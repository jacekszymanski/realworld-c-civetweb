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

user_t *db_find_user_by_email(sqlite3 *db, const char *email) {
  user_t *user = NULL;

  if (email == NULL || strlen(email) == 0 || open_db(&db) < 0) {
    return NULL;
  }

  sqlite3_stmt *stmt;
  SQLITE_DO_OR_DIE_NULL(db, sqlite3_prepare_v2(db,
      "SELECT id, username, email, bio, image, password FROM users WHERE email = ?", -1, &stmt, NULL));

  SQLITE_DO_OR_DIE_NULL(db, sqlite3_bind_text(stmt, 1, email, -1, SQLITE_STATIC));

  // execute statement
  int rc = sqlite3_step(stmt);

  if (rc == SQLITE_ROW) {
    DLOG("found user %s\n", email);
    user = user_create(
      safe_strdup((const char *)sqlite3_column_text(stmt, 2)), // email
      safe_strdup((const char *)sqlite3_column_text(stmt, 5)), // abusing token field for password
      safe_strdup((const char *)sqlite3_column_text(stmt, 1)), // username
      safe_strdup((const char *)sqlite3_column_text(stmt, 3)), // bio
      safe_strdup((const char *)sqlite3_column_text(stmt, 4))  // image
    );

    if (user == NULL) {
      WLOGS("Cannot create user object");
    }
    else {
      VLOGS("created user object");
    }
  }
  else {
    SQLITE_DIE(db, NULL);
  }

  sqlite3_finalize(stmt);

  return user;
}

user_t *db_find_user_by_username(sqlite3 *db, const char *username) {
  user_t *user = NULL;

  if (username == NULL || strlen(username) == 0 || open_db(&db) < 0) {
    return NULL;
  }

  sqlite3_stmt *stmt;

  SQLITE_DO_OR_DIE_NULL(db, sqlite3_prepare_v2(db,
      "SELECT id, username, email, bio, image, password FROM users WHERE username = ?", -1, &stmt, NULL));

  SQLITE_DO_OR_DIE_NULL(db, sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC));

  SQLITE_DO_OR_DIE_NULL_RC(db, sqlite3_step(stmt), SQLITE_ROW);
  DLOG("found user %s\n", username);
  user = user_create(
      safe_strdup((const char *)sqlite3_column_text(stmt, 2)), // email
      safe_strdup((const char *)sqlite3_column_text(stmt, 5)), // abusing token field for password
      safe_strdup((const char *)sqlite3_column_text(stmt, 1)), // username
      safe_strdup((const char *)sqlite3_column_text(stmt, 3)), // bio
      safe_strdup((const char *)sqlite3_column_text(stmt, 4))  // image
  );

  if (user == NULL) {
    WLOGS("Cannot create user object");
  }
  else {
    VLOGS("created user object");
  }

  sqlite3_finalize(stmt);

  return user;

}

#define PROFILE_QUERY   "SELECT " \
      "u.username, u.bio, u.image, " \
      "(SELECT COUNT(*) FROM follows " \
        "WHERE followed = u.id and " \
        " follower = (SELECT u2.id FROM users u2 WHERE u2.username = ?)) as following " \
      "FROM users u WHERE u.username = ?"

profile_t *db_get_profile_by_username(sqlite3 *db, const char *username, const char *current_username) {
  profile_t *profile = NULL;

  if (username == NULL || strlen(username) == 0 || open_db(&db) < 0) {
    return NULL;
  }

  // a hack: user cannot follow themself, so if no user is logged in it will make
  // the "following" field 0
  const char *otheruser = current_username ? current_username : username;

  sqlite3_stmt *stmt;

  SQLITE_DO_OR_DIE_NULL(db, sqlite3_prepare_v2(db, PROFILE_QUERY, -1, &stmt, NULL));

  SQLITE_DO_OR_DIE_NULL(db, sqlite3_bind_text(stmt, 1, otheruser, -1, SQLITE_STATIC));
  SQLITE_DO_OR_DIE_NULL(db, sqlite3_bind_text(stmt, 2, username, -1, SQLITE_STATIC));

  SQLITE_DO_OR_DIE_NULL_RC(db, sqlite3_step(stmt), SQLITE_ROW);

  DLOG("found profile %s\n", username);
  profile = profile_create(
      safe_strdup((const char *)sqlite3_column_text(stmt, 0)), // username
      safe_strdup((const char *)sqlite3_column_text(stmt, 1)), // bio
      safe_strdup((const char *)sqlite3_column_text(stmt, 2)), // image
      sqlite3_column_int(stmt, 3)                              // followers
  );

  if (profile == NULL) {
    WLOGS("Cannot create profile object");
  }
  else {
    VLOGS("created profile object");
  }

  sqlite3_finalize(stmt);

  return profile;
}

#undef PROFILE_QUERY
