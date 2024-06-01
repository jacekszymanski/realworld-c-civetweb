#include <sqlite3.h>
#include <stdio.h>
#include <string.h>

#include "db.h"

#include <app/log.h>
#include <app/util.h>
#include <app/appctx.h>

#include <openapi/model/user.h>
#include <openapi/model/profile.h>

struct table {
  const char *name;
  const char *sql;
};

const struct table tables[] = {
    { .name = "users",
      .sql = "CREATE TABLE IF NOT EXISTS users ("
             "id INTEGER PRIMARY KEY AUTOINCREMENT,"
             "email TEXT NOT NULL,"
             "username TEXT NOT NULL,"
             "password TEXT NOT NULL,"
             "bio TEXT,"
             "image TEXT,"
             "UNIQUE(email),"
             "UNIQUE(username)"
             ");"
    },
    { .name = "articles",
      .sql = "CREATE TABLE IF NOT EXISTS articles ("
             "id INTEGER PRIMARY KEY AUTOINCREMENT,"
             "title TEXT NOT NULL,"
             "description TEXT NOT NULL,"
             "body TEXT NOT NULL,"
             "author INTEGER NOT NULL,"
             "created_at INTEGER NOT NULL,"
             "updated_at INTEGER NOT NULL,"
             "FOREIGN KEY(author) REFERENCES users(id)"
             ");"
    },
    { .name = "comments",
      .sql = "CREATE TABLE IF NOT EXISTS comments ("
             "id INTEGER PRIMARY KEY AUTOINCREMENT,"
             "body TEXT NOT NULL,"
             "author INTEGER NOT NULL,"
             "article INTEGER NOT NULL,"
             "created_at INTEGER NOT NULL,"
             "FOREIGN KEY(author) REFERENCES users(id),"
             "FOREIGN KEY(article) REFERENCES articles(id)"
             ");"
    },
    { .name = "favorites",
      .sql = "CREATE TABLE IF NOT EXISTS favorites ("
             "user INTEGER NOT NULL,"
             "article INTEGER NOT NULL,"
             "FOREIGN KEY(user) REFERENCES users(id),"
             "FOREIGN KEY(article) REFERENCES articles(id),"
             "UNIQUE(user, article)"
             ");"
    },
    { .name = "follows",
      .sql = "CREATE TABLE IF NOT EXISTS follows ("
             "follower INTEGER NOT NULL,"
             "followed INTEGER NOT NULL,"
             "FOREIGN KEY(follower) REFERENCES users(id),"
             "FOREIGN KEY(followed) REFERENCES users(id),"
             "UNIQUE(follower, followed)"
             ");"
    },
    { .name = "tags",
      .sql = "CREATE TABLE IF NOT EXISTS article_tags ("
             "article INTEGER NOT NULL,"
             "tag TEXT NOT NULL,"
             "FOREIGN KEY(article) REFERENCES articles(id),"
             "FOREIGN KEY(tag) REFERENCES tags(id),"
             "UNIQUE(article, tag)"
             ");"
    },
    { .name = NULL }
};

sqlite3 *__db; // only used with single db mode

int _open_db(sqlite3 **db, int flags) {
  int rc = sqlite3_open_v2(appctx.dbpath, db, flags, NULL);

  if (rc != SQLITE_OK || sqlite3_db_readonly(*db, NULL)) {
    WLOG("Cannot open database for writing: %s\n", sqlite3_errmsg(*db));
    sqlite3_close(*db);
    return -1;
  }

  VLOGS("opened database");

  return 0;
}

int open_db(sqlite3 **db) {
  if (appctx.__singledb) {
    if (__db) {
      *db = __db;
      return 0;
    }
    else {
      WLOGS("singledb enabled, but no db open");
      return -1;
    }
  }
  else {
    return _open_db(db, SQLITE_OPEN_READWRITE);
  }
}

int __close_db(sqlite3 *db, int notreally) {
  if (notreally) {
    return 0;
  }

  int rc = sqlite3_close(db);
  if (rc != SQLITE_OK) {
    WLOG("Cannot close database: %s\n", sqlite3_errmsg(db));
    return -1;
  }

  VLOGS("closed database");
  return 0;
}

int close_db(sqlite3 *db) {
  return __close_db(db, appctx.__singledb);
}

int shutdown_db() {
  return __close_db(__db, !appctx.__singledb);
}

int create_db(sqlite3 **db) {
  if (__db) {
    // wrong state here, handle already registered and still trying to create
    WLOGS("create_db: db already open");
    return -1;
  }
  return _open_db(db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE);
}

int check_and_init_db(const char *dbpath) {
  sqlite3 *db;

  /* check if file exists, if not, need to init the database */
  int needInit = 1;
  FILE *fp = fopen(dbpath, "r");
  if (fp != NULL) {
    needInit = 0;
    fclose(fp);
  }

  if (needInit) {

    if (create_db(&db) < 0) {
      return -1;
    }

    /* init the database */
    for (int i = 0; tables[i].name; i++) {
      DLOG("init table %s\n", tables[i].name);
      int rc = sqlite3_exec(db, tables[i].sql, NULL, NULL, NULL);
      if (rc != SQLITE_OK) {
        WLOG("Cannot init table %s: %s\n", tables[i].name, sqlite3_errmsg(db));
        sqlite3_close(db);
        return -2;
      }
    }
  }
  else {
    if (_open_db(&db, SQLITE_OPEN_READWRITE) < 0) {
      return -3;
    }
  }

  if (appctx.__singledb) {
    __db = db;
  }
  else {
    sqlite3_close(db);
  }

  return 0;
}

int db_create_user(sqlite3 *db, const char* username, const char* email, const char* password) {

  // TODO better checks on username, email, password
  if (username == NULL
        || email == NULL
        || password == NULL
        || strlen(username) == 0
        || strlen(email) == 0
        || strlen(password) == 0
        || open_db(&db) < 0
      ) {
    return -1;
  }

  sqlite3_stmt *stmt;
  SQLITE_DO_OR_DIE(db, sqlite3_prepare_v2(db,
      "INSERT INTO users (username, email, password) VALUES (?, ?, ?)", -1, &stmt, NULL));

  int idx = 1;
  SQLITE_DO_OR_DIE(db, sqlite3_bind_text(stmt, idx++, username, -1, SQLITE_STATIC));
  SQLITE_DO_OR_DIE(db, sqlite3_bind_text(stmt, idx++, email, -1, SQLITE_STATIC));
  SQLITE_DO_OR_DIE(db, sqlite3_bind_text(stmt, idx++, password, -1, SQLITE_STATIC));

  SQLITE_DO_OR_DIE_RC(db, sqlite3_step(stmt), SQLITE_DONE);

  DLOG("created user %s %s\n", username, email);

  sqlite3_finalize(stmt);

  return 0;

}

#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsequence-point"
#endif

#define SQLITE_GET(type) SQLITE_GET_##type(stmt, idx++)
#define SQLITE_GET_text(stmt, idx) safe_strdup((const char *)sqlite3_column_text(stmt, idx))
#define SQLITE_GET_int(stmt, idx) sqlite3_column_int(stmt, idx)

#define DB_FIND_OBJECT_FN(name, ...) \
  name##_t *db_find_##name(sqlite3 *db, const char *query, int param_cnt, int param_types[], void* param_values[]) { \
    name##_t *name = NULL; \
    \
    if (open_db(&db) < 0 || query == NULL ||  param_types == NULL || param_values == NULL) { \
      return NULL; \
    } \
    \
    for (int i = 0; i < param_cnt; i++) { \
      if (param_values[i] == NULL )  { \
        return NULL; \
      } \
    } \
    \
    sqlite3_stmt *stmt; \
    \
    SQLITE_DO_OR_DIE_NULL(db, sqlite3_prepare_v2(db, query, -1, &stmt, NULL)); \
    \
    for (int i = 0; i < param_cnt; i++) { \
      switch (param_types[i]) { \
        case SQLITE_INTEGER: \
          SQLITE_DO_OR_DIE_NULL(db, sqlite3_bind_int(stmt, i + 1, *((int *)(param_values[i])))); \
          break; \
        case SQLITE_TEXT: \
          SQLITE_DO_OR_DIE_NULL(db, sqlite3_bind_text(stmt, i + 1, (const char *)param_values[i], -1, SQLITE_STATIC)); \
          break; \
        default: \
          return NULL; \
      } \
    } \
    \
    SQLITE_DO_OR_DIE_NULL_RC(db, sqlite3_step(stmt), SQLITE_ROW); \
    DLOGS("found " #name " %s\n"); \
    int idx = 0; \
    name = name##_create( \
       FOR_EACH_L(SQLITE_GET, __VA_ARGS__) \
    ); \
    \
    if (name == NULL) { \
      WLOGS("Cannot create " #name " object"); \
    } \
    else { \
      VLOGS("created " #name " object"); \
    } \
    \
    sqlite3_finalize(stmt); \
    \
    return name; \
  }

DB_FIND_OBJECT_FN(user, text, text, text, text, text)
DB_FIND_OBJECT_FN(profile, text, text, text, int)

// TODO verify this in clang
#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif

#define USER_QUERY(param) "SELECT username, email, bio, image, password FROM users WHERE " param " = ?"
user_t *db_find_user_by_username(sqlite3 *db, const char *username) {
  return db_find_user(db,
        USER_QUERY("username"), 1, (int[]){SQLITE_TEXT}, (void*[]){(void *)username});
}

user_t *db_find_user_by_email(sqlite3 *db, const char *email) {
  return db_find_user(db,
        USER_QUERY("email"), 1, (int[]){SQLITE_TEXT}, (void*[]){(void *)email});
}
#undef USER_QUERY

#define PROFILE_QUERY   "SELECT " \
      "u.username, u.bio, u.image, " \
      "(SELECT COUNT(*) FROM follows " \
        "WHERE followed = u.id and " \
        " follower = (SELECT u2.id FROM users u2 WHERE u2.username = ?)) as following " \
      "FROM users u WHERE u.username = ?"

profile_t *db_get_profile_by_username(sqlite3 *db, const char *username, const char *current_username) {
  const char *cur_username = current_username ? current_username : username;
  return db_find_profile(db, PROFILE_QUERY, 2, (int[]){SQLITE_TEXT, SQLITE_TEXT},
      (void*[]){(void *)cur_username, (void *)username});
}

#undef PROFILE_QUERY
