#include <sqlite3.h>
#include <stdio.h>
#include <string.h>

#include "db.h"
#include "log.h"
#include "util.h"

#include "openapi/model/user.h"

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

int _open_db(sqlite3 **db, int flags) {
  int rc = sqlite3_open_v2(dbpath, db, flags, NULL);

  if (rc != SQLITE_OK || sqlite3_db_readonly(*db, NULL)) {
    WLOG("Cannot open database for writing: %s\n", sqlite3_errmsg(*db));
    sqlite3_close(*db);
    return -1;
  }

  VLOGS("opened database");

  return 0;
}

int open_db(sqlite3 **db) {
  return _open_db(db, SQLITE_OPEN_READWRITE);
}

int create_db(sqlite3 **db) {
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

  if (!needInit) {
    return 0;
  }

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

  sqlite3_close(db);

  return 0;
}

int db_create_user(const char* username, const char* email, const char* password) {
  sqlite3 *db;

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
  int rc = sqlite3_prepare_v2(db, "INSERT INTO users (username, email, password) VALUES (?, ?, ?)", -1, &stmt, NULL);
  if (rc != SQLITE_OK) {
    WLOG("Cannot prepare statement: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    return -2;
  }


  rc = sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
  if (rc != SQLITE_OK) {
    WLOG("Cannot bind username: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    return -3;
  }

  rc = sqlite3_bind_text(stmt, 2, email, -1, SQLITE_STATIC);
  if (rc != SQLITE_OK) {
    WLOG("Cannot bind email: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    return -4;
  }

  rc = sqlite3_bind_text(stmt, 3, password, -1, SQLITE_STATIC);
  if (rc != SQLITE_OK) {
    WLOG("Cannot bind password: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    return -5;
  }

  rc = sqlite3_step(stmt);
  if (rc != SQLITE_DONE) {
    WLOG("Cannot step statement: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    return -6;
  }

  DLOG("created user %s %s\n", username, email);

  sqlite3_finalize(stmt);
  sqlite3_close(db);

  return 0;

}

user_t *db_find_user_by_email(const char *email) {
  user_t *user = NULL;
  sqlite3 *db;

  if (email == NULL || strlen(email) == 0 || open_db(&db) < 0) {
    return NULL;
  }

  sqlite3_stmt *stmt;
  int rc = sqlite3_prepare_v2(db, "SELECT id, username, email, bio, image, password FROM users WHERE email = ?", -1, &stmt, NULL);
  if (rc != SQLITE_OK) {
    WLOG("Cannot prepare statement: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    return NULL;
  }

  rc = sqlite3_bind_text(stmt, 1, email, -1, SQLITE_STATIC);
  if (rc != SQLITE_OK) {
    WLOG("Cannot bind email: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    return NULL;
  }

  // execute statement
  rc = sqlite3_step(stmt);

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

  sqlite3_finalize(stmt);
  sqlite3_close(db);

  return user;
}

user_t *db_find_user_by_username(const char *username) {
  sqlite3 *db;
  user_t *user = NULL;

  if (username == NULL || strlen(username) == 0 || open_db(&db) < 0) {
    return NULL;
  }

  sqlite3_stmt *stmt;
  int rc = sqlite3_prepare_v2(db, "SELECT id, username, email, bio, image, password FROM users WHERE username = ?", -1, &stmt, NULL);
  if (rc != SQLITE_OK) {
    WLOG("Cannot prepare statement: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    return NULL;
  }


  rc = sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
  if (rc != SQLITE_OK) {
    WLOG("Cannot bind username: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    return NULL;
  }

  // execute statement
  rc = sqlite3_step(stmt);

  if (rc == SQLITE_ROW) {
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

  }

  sqlite3_finalize(stmt);
  sqlite3_close(db);

  return user;

}
