#ifndef __DB_H__
#define __DB_H__

#include <sqlite3.h>

#include <openapi/model/user.h>
#include <openapi/model/profile.h>

int check_and_init_db(const char* db_path);

int db_create_user(sqlite3 *db, const char* username, const char* email, const char* password);

user_t *db_find_user_by_email(sqlite3 *db, const char* email);
user_t *db_find_user_by_username(sqlite3 *db, const char* username);

profile_t *db_get_profile_by_username(sqlite3 *db, const char* username, const char* current_username);

int open_db(sqlite3** db);
int close_db(sqlite3* db);
int shutdown_db();

#define SQLITE_DIE(db, ret) do { \
    WLOG("database error: %s\n", sqlite3_errmsg(db)); \
    return (ret); \
  } while (0)

#define SQLITE_DO_OR_DIE_RC_RET(db, what, rcok, ret) do { \
    int __rc = what; \
    if (__rc != (rcok)) { \
      SQLITE_DIE(db, ret); \
    } \
  } while (0)

#define SQLITE_DO_OR_DIE_RET(db, what, ret) SQLITE_DO_OR_DIE_RC_RET(db, what, SQLITE_OK, ret)

#define SQLITE_DO_OR_DIE_RC(db, what, rcok) SQLITE_DO_OR_DIE_RC_RET(db, what, rcok, -1)
#define SQLITE_DO_OR_DIE(db, what) SQLITE_DO_OR_DIE_RET(db, what, -1)

#define SQLITE_DO_OR_DIE_NULL_RC(db, what, rcok) SQLITE_DO_OR_DIE_RC_RET(db, what, rcok, NULL)
#define SQLITE_DO_OR_DIE_NULL(db, what) SQLITE_DO_OR_DIE_NULL_RC(db, what, SQLITE_OK)

#endif // __DB_H__
