#ifndef __DB_H__
#define __DB_H__

#include <sqlite3.h>

int check_and_init_db(const char* db_path);

#endif // __DB_H__
