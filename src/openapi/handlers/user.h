#ifndef __HANDLERS_USER_H__
#define __HANDLERS_USER_H__

#include <civetweb.h>

int create_user_handler(struct mg_connection *conn, void *cbdata);

#endif // __HANDLERS_USER_H__
