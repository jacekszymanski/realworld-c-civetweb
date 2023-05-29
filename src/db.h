#ifndef __DB_H__
#define __DB_H__

#include <sqlite3.h>

extern char* dbpath;

int check_and_init_db(const char* db_path);

int db_create_user(const char* username, const char* email, const char* password);

#endif // __DB_H__
