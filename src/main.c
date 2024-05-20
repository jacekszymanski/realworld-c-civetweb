#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "platform/platform.h"

#include <civetweb.h>
#include <sqlite3.h>

#include "stubs.h"
#include "db.h"
#include "log.h"

#include "openapi/handlers/user.h"

#define DBPATH "data/conduit.db"

struct appctx appctx;

int main(int argc, char *argv[]) {
  (void)argc;
  (void)argv;

  const char *cw_options[] = {
    "listening_ports", "8080",
    "request_timeout_ms", "2000",
    "error_log_file", "error.log",
    0
  };

  struct mg_callbacks callbacks;
  struct mg_context *ctx;

  appctx.__singledb = 1;
  appctx.dbpath = DBPATH;

  check_and_init_db(DBPATH);

  memset(&callbacks, 0, sizeof(callbacks));

  ctx = mg_start(&callbacks, 0, cw_options);

  if (ctx == NULL) {
    ELOG("%s", "Failed to start server.\n");
    return EXIT_FAILURE;
  }

  install_stubs(ctx);
  mg_set_request_handler(ctx, "/api/users", request_handler, create_user_handler);
  mg_set_request_handler(ctx, "/api/users/login", request_handler, login_handler);
  mg_set_request_handler(ctx, "/api/user", request_handler, get_current_user_handler);
  mg_set_request_handler(ctx, "/api/profiles/*", request_handler, get_profile_handler);

  while (1) {
    sleep(1);
  }

  mg_stop(ctx);

  shutdown_db();

  return EXIT_SUCCESS;
}
