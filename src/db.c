#include <sqlite3.h>
#include <stdio.h>

int check_and_init_db(char* dbpath, sqlite3 **db) {

  /* check if file exists, if not, need to init the database */
  int needInit = 1;
  FILE *fp = fopen(dbpath, "r");
  if (fp != NULL) {
    needInit = 0;
    fclose(fp);
  }

  int rc = sqlite3_open_v2(dbpath, db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL);

  if (rc != SQLITE_OK || sqlite3_db_readonly(*db, NULL)) {
    fprintf(stderr, "Cannot open database for writing: %s\n", sqlite3_errmsg(*db));
    sqlite3_close(*db);
    return 1;
  }

  if (needInit) {
    /* init the database */
  }

  return 0;

}
