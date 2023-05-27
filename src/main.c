#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "platform/platform.h"

#include <civetweb.h>
#include <sqlite3.h>

#include "stubs.h"
#include "db.h"

#define DBPATH "data/conduit.db"

int main(int argc, char *argv[]) {
  const char *cw_options[] = {
    "listening_ports", "8080",
    "request_timeout_ms", "2000",
    "error_log_file", "error.log",
    0
  };

  struct mg_callbacks callbacks;
  struct mg_context *ctx;

  sqlite3 *db;

  memset(&callbacks, 0, sizeof(callbacks));

  ctx = mg_start(&callbacks, 0, cw_options);

  if (ctx == NULL) {
    fprintf(stderr, "Failed to start server.\n");
    return EXIT_FAILURE;
  }

  install_stubs(ctx);
  check_and_init_db(DBPATH, &db);

  while (1) {
    sleep(1);
  }

  mg_stop(ctx);

  sqlite3_close(db);

  return EXIT_SUCCESS;

}
