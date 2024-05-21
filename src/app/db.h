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

#endif // __DB_H__
