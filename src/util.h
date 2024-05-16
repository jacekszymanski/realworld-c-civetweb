#ifndef __UTIL_H__
#define __UTIL_H__

#include <civetweb.h>
#include <cjson/cJSON.h>

#include "appctx.h"

const char* get_request_content(struct mg_connection* conn);
char* safe_strdup(const char* s);
void set_200_ok(struct reqctx* ctx);
void reqctx_cleanup(struct reqctx* ctx);

void reqctx_set_error(struct reqctx* ctx, int code, const char* msg);
void reqctx_set_errorf(struct reqctx* ctx, int code, const char* fmt, ...);
void reqctx_set_response(struct reqctx* ctx, int code, cJSON* json);
void reqctx_set_resp_msg(struct reqctx* ctx, int code, cJSON* json, const char* msg);

#endif // __UTIL_H__
