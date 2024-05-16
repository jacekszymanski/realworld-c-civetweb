#include <civetweb.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <cjson/cJSON.h>

#include "util.h"
#include "log.h"
#include "appctx.h"

#include "openapi/model/user.h"

#define BUF_INCR 4096

const char* read_body_frags(struct mg_connection *conn);

const char* get_request_content(struct mg_connection *conn) {
  const struct mg_request_info *ri = mg_get_request_info(conn);
  int content_length = ri->content_length;
  char *content;
  if (content_length == 0) {
    return NULL;
  }
  else if (content_length < 0) {
    return read_body_frags(conn);
  }
  else {
    content = malloc(content_length + 1);
    int read = mg_read(conn, content, content_length);
    content[read] = '\0';
    DLOG("get_request_content: read %d bytes\n", read);
  }

  return content;
}

const char* read_body_frags(struct mg_connection *conn) {
  // content-length is not available, need to read as it comes

  // allocate buffer, if needed it will be increased by BUF_INCR
  int bufsize = BUF_INCR;
  char *buf = malloc(bufsize + 1);

  int read = 0;
  int total_read = 0;

  // 0 might mean that more data is to come... OTOH it is also documented as closed connection...
  while ((read = mg_read(conn, buf + total_read, bufsize - total_read)) >= 0) {
    total_read += read;
    if (total_read + 1 >= bufsize) {
      bufsize += BUF_INCR;
      char* oldbuf = buf;
      buf = realloc(buf, bufsize + 1);
      if (buf == NULL) {
        WLOG("%s", "read_body_frags: realloc failed\n");
        free(oldbuf);
        return NULL;
      }

    }
  }

  buf[total_read] = '\0';

  DLOG("read_body_frags: read %d bytes\n", total_read);

  return buf;
}

char * safe_strdup(const char *s) {
  if (s == NULL) {
    return strdup("");
  }
  return strdup(s);
}

// TODO get rid of this function
void set_200_ok(struct reqctx *ctx) {
  ctx->respcode = 200;
  ctx->errmsg = strdup("OK");
}

void reqctx_cleanup(struct reqctx *ctx) {
  if (ctx->errmsg) {
    free(ctx->errmsg);
  }
  if (ctx->curuser) {
    user_free(ctx->curuser);
  }
  if (ctx->respjson) {
    cJSON_Delete(ctx->respjson);
  }
}

#define CHK_SEALED(ctx) if ((ctx)->respsealed) { WLOGS("reqctx: response already sealed, ignoring"); return; }

void reqctx_set_error(struct reqctx *ctx, int code, const char *msg) {
  CHK_SEALED(ctx);
  SFREE(ctx->errmsg);
  ctx->respcode = code;
  if(msg) ctx->errmsg = strdup(msg);
}

void reqctx_set_errorf(struct reqctx *ctx, int code, const char *fmt, ...) {
  CHK_SEALED(ctx);
  SFREE(ctx->errmsg);
  va_list args;
  va_start(args, fmt);
  char *msg;
  vasprintf(&msg, fmt, args);
  va_end(args);
  reqctx_set_error(ctx, code, msg);
  free(msg);
}

void reqctx_set_response(struct reqctx *ctx, int code, cJSON *json) {
  CHK_SEALED(ctx);
  ctx->respcode = code;
  ctx->respjson = json;
}

void reqctx_set_resp_msg(struct reqctx *ctx, int code, cJSON *json, const char *msg)  {
  CHK_SEALED(ctx);
  SFREE(ctx->errmsg);
  ctx->respcode = code;
  ctx->respjson = json;
  ctx->errmsg = strdup(msg);
}

#undef CHK_SEALED
