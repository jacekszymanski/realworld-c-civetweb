#ifndef __DB_H__
#define __DB_H__

#include <sqlite3.h>
#include "openapi/model/user.h"

extern char* dbpath;

int check_and_init_db(const char* db_path);

int db_create_user(const char* username, const char* email, const char* password);

user_t *db_find_user_by_email(const char* email);

#endif // __DB_H__
