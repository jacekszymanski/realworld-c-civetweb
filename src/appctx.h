#ifndef __APPCTX_H__
#define __APPCTX_H__

#include <string.h>
#include <sqlite3.h>
#include <civetweb.h>
#include "macros.h"
#include "openapi/model/user.h"

struct reqctx {
  struct mg_connection *conn;
  int respcode;
  char *errmsg;
  int respsent;
  user_t *curuser;
  sqlite3 *db;
};

typedef struct reqctx reqctx_t;
typedef int handler_t(reqctx_t *ctx);

struct appctx {
  int __singledb; // whether to use a single db connection, requires Sqlite's serialized mode
  char* dbpath;
};

extern struct appctx appctx;

// default to internal server error, change only if sure of success
#define REQCTX_INIT(conn, db) { conn, 500, strdup("Internal Server Error"), 0, NULL, db }
#define REQCTX_FREE(ctx) do { SFREE(ctx->errmsg); } while (0)
#define REQCTX_SET_ERROR(ctx, code, msg) do { ctx->respcode = code; SFREE(ctx->errmsg); ctx->errmsg = strdup(msg); } while (0)


#endif // __APPCTX_H__
