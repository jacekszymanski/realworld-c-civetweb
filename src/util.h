#ifndef __UTIL_H__
#define __UTIL_H__

#include <civetweb.h>
#include "appctx.h"

const char* get_request_content(struct mg_connection* conn);
char* safe_strdup(const char* s);
void set_200_ok(struct reqctx* ctx);

#endif // __UTIL_H__
