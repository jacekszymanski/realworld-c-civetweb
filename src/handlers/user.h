#ifndef __HANDLERS_USER_H__
#define __HANDLERS_USER_H__

#include <civetweb.h>

#include <app/appctx.h>

int request_handler(struct mg_connection *conn, void *cbdata);

int create_user_handler(struct reqctx *ctx);
int login_handler(struct reqctx *ctx);
int get_current_user_handler(struct reqctx *ctx);
int get_profile_handler(struct reqctx *ctx);

#endif // __HANDLERS_USER_H__
