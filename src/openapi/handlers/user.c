#include <cjson/cJSON.h>
#include <civetweb.h>
#include <string.h>

#include "../api/UserAndAuthenticationAPI.h"
#include "../model/create_user_request.h"
#include "../model/generic_error_model.h"
#include "../model/login_200_response.h"
#include "../model/login_request.h"

#include "../../util.h"
#include "../../log.h"
#include "../../macros.h"
#include "../../db.h"

// forward decls to be moved to util
int send_response(struct reqctx *ctx, cJSON* response_json);
cJSON* parse_json_body(struct mg_connection* conn);
int verify_logged_in(struct reqctx *ctx, int must);

int create_user_handler(struct reqctx *ctx) {
  struct mg_connection* conn = ctx->conn;

  const struct mg_request_info* ri = mg_get_request_info(conn);
  DLOG("create_user_handler: %s\n", ri->local_uri);

  const char* rawbody = get_request_content(conn);

  cJSON* jsonbody = cJSON_Parse(rawbody);

  free((void*)rawbody);

  if (jsonbody == NULL) {
    WLOGS("  failed to parse request body\n");
    mg_send_http_error(conn, 500, "failed to parse request body");
    return 1;
  }

  create_user_request_t* body = create_user_request_parseFromJSON(jsonbody);
  cJSON_Delete(jsonbody);

  if (body == NULL) {
    WLOGS("  failed to parse request body\n");
    mg_send_http_error(conn, 500, "failed to parse request body");
    return 1;
  }
  TLOGS("  parsed request body");

  login_200_response_t* response = UserAndAuthenticationAPI_createUser(ctx, body);
  create_user_request_free(body);
  VLOGS("freed body");

  if (response == NULL) {
    WLOGS("  failed to create user");
    mg_send_http_error(conn, 500, "failed to create user");
    return 1;
  }
  TLOGS("  created user");

  cJSON* response_json = login_200_response_convertToJSON(response);
  VLOGS("freeing response");
  login_200_response_free(response);
  VLOGS("freed response");

  if (response_json == NULL) {
    WLOGS("  failed to convert response to json");
    mg_send_http_error(conn, 500, "failed to convert response to json");
    return 1;
  }
  TLOGS("  converted response to json");

  char* response_json_str = cJSON_PrintUnformatted(response_json);
  cJSON_Delete(response_json);
  VLOGS("freed response json");

  if (response_json_str == NULL) {
    WLOGS("  failed to convert response to json string\n");
    mg_send_http_error(conn, 500, "failed to convert response to json string");
    return 1;
  }
  TLOGS("  converted response to json string");

  mg_printf(conn, "HTTP/1.1 200 OK\r\n");
  mg_printf(conn, "Content-Type: application/json\r\n");
  mg_printf(conn, "Content-Length: %d\r\n", (int)strlen(response_json_str));
  mg_printf(conn, "\r\n");
  mg_printf(conn, "%s", response_json_str);
  free(response_json_str);
  VLOGS("  freed response json string");
  TLOGS("  sent response");

  return 0;
}

int login_handler(struct reqctx *ctx) {
  cJSON* jsonbody = parse_json_body(ctx->conn);

  NULL_FAIL_FAST(ctx, jsonbody, 1, "parse request body");

  login_request_t* body = login_request_parseFromJSON(jsonbody);

  cJSON_Delete(jsonbody);

  NULL_FAIL_FAST(ctx, body, 1, "parse request body");
  TLOGS("parsed request body");

  login_200_response_t* response = UserAndAuthenticationAPI_login(ctx, body);
  login_request_free(body);
  VLOGS("freed body");

  NULL_FAIL_FAST(ctx, response, 1, "login user");
  TLOGS("logged in user");

  cJSON* response_json = login_200_response_convertToJSON(response);
  login_200_response_free(response);
  VLOGS("freed response");

  NULL_FAIL_FAST(ctx, response_json, 1, "convert response to json");
  TLOGS("converted response to json");

  set_200_ok(ctx);

  int ret = send_response(ctx, response_json);
  cJSON_Delete(response_json);
  VLOGS("freed response json");

  return ret;
}

int get_current_user_handler(struct reqctx *ctx) {
  verify_logged_in(ctx, 1);
  RESP_SENT_FAIL_FAST(ctx, 1);

  login_200_response_t* response = UserAndAuthenticationAPI_getCurrentUser(ctx);

  NULL_FAIL_FAST(ctx, response, 1, "get current user");
  TLOGS("got current user");

  cJSON* response_json = login_200_response_convertToJSON(response);
  login_200_response_free(response);
  VLOGS("freed response");

  NULL_FAIL_FAST(ctx, response_json, 1, "convert response to json");
  TLOGS("converted response to json");

  set_200_ok(ctx);

  int ret = send_response(ctx, response_json);
  cJSON_Delete(response_json);
  VLOGS("freed response json");

  return ret;
}

// request_handler takes the real handler as cbdata and manages reqctx
int request_handler(struct mg_connection* conn, void* cbdata) {
  handler_t* handler = (handler_t*)cbdata;

  struct reqctx ctx = REQCTX_INIT(conn);

  int ret = handler(&ctx);

  reqctx_cleanup(&ctx);

  return ret;

}

// TODO move to util
int send_response(struct reqctx *ctx, cJSON* response_json) {
  char *response_json_str = cJSON_PrintUnformatted(response_json);
  struct mg_connection* conn = ctx->conn;

  NULL_FAIL_FAST(ctx, response_json_str, 1, "convert response to json string");
  TLOGS("converted response to json string");

  mg_printf(conn, "HTTP/1.1 %3d %s\r\n", ctx->respcode, ctx->errmsg);
  mg_printf(conn, "Content-Type: application/json\r\n");
  mg_printf(conn, "Content-Length: %d\r\n", (int)strlen(response_json_str));
  mg_printf(conn, "\r\n");
  mg_printf(conn, "%s", response_json_str);
  free(response_json_str);
  VLOGS("  freed response json string");
  TLOGS("  sent response");

  return 0;
}


// TODO move to util
cJSON* parse_json_body(struct mg_connection* conn) {

  const struct mg_request_info* ri = mg_get_request_info(conn);
  DLOG("parse_json_body: %s\n", ri->local_uri);

  const char* rawbody = get_request_content(conn);

  cJSON* jsonbody = cJSON_Parse(rawbody);

  free((void*)rawbody);

  return jsonbody;

}

// if must is 1, the user must be logged in; if 0, then not logged in is ok,
// but if Authorization header is present, it must be for a valid user
int verify_logged_in(struct reqctx *ctx, int must) {
  const char* auth_header = mg_get_header(ctx->conn, "Authorization");
  if (must) {
    NULL_FAIL_FAST(ctx, auth_header, 1, "get Authorization header");
  }
  else {
    if (auth_header == NULL) {
      return 0;
    }
  }

  if (strncmp(auth_header, "Token ", 6) != 0) {
    const char* error_message = "Authorization header does not start with 'Token '";
    WLOGS(error_message);
    REQCTX_SET_ERROR(ctx, 401, error_message);
    mg_send_http_error(ctx->conn, 401, "%s", error_message);
    ctx->respsent = 1;
    return 1;
  }

  // for now the "token" is simply the username, so extract and find the user
  const char* username = auth_header + 6;
  user_t* user = db_find_user_by_username(username);

  if (user == NULL) {
    const char* error_message = "Access token is invalid";
    WLOGS(error_message);
    REQCTX_SET_ERROR(ctx, 401, error_message);
    mg_send_http_error(ctx->conn, 401, "%s", error_message);
    ctx->respsent = 1;
    return 1;
  }

  ctx->curuser = user;
  return 0;

}
