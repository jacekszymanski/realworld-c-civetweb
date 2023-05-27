#include <sqlite3.h>
#include <stdio.h>

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

int check_and_init_db(char *dbpath, sqlite3 **db) {

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
    for (int i = 0; tables[i].name; i++) {
      fprintf(stderr, "init table %s\n", tables[i].name);
      rc = sqlite3_exec(*db, tables[i].sql, NULL, NULL, NULL);
      if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot init table %s: %s\n", tables[i].name, sqlite3_errmsg(*db));
        sqlite3_close(*db);
        return 1;
      }
    }
  }

  return 0;
}
