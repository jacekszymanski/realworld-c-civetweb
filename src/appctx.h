#ifndef __APPCTX_H__
#define __APPCTX_H__

#include <string.h>
#include "macros.h"

struct reqctx {
  struct mg_connection *conn;
  int respcode;
  char *errmsg;
  int respsent;
};

// default to internal server error, change only if sure of success
#define REQCTX_INIT(conn) { conn, 500, strdup("Internal Server Error"), 0 }
#define REQCTX_FREE(ctx) do { SFREE(ctx->errmsg); } while (0)
#define REQCTX_SET_ERROR(ctx, code, msg) do { ctx->respcode = code; SFREE(ctx->errmsg); ctx->errmsg = strdup(msg); } while (0)

#endif // __APPCTX_H__
