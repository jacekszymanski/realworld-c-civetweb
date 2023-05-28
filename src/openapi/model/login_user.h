/*
 * login_user.h
 *
 * 
 */

#ifndef _login_user_H_
#define _login_user_H_

#include <string.h>
#include <cjson/cJSON.h>
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct login_user_t login_user_t;




typedef struct login_user_t {
    char *email; // string
    char *password; // string

} login_user_t;

login_user_t *login_user_create(
    char *email,
    char *password
);

void login_user_free(login_user_t *login_user);

login_user_t *login_user_parseFromJSON(cJSON *login_userJSON);

cJSON *login_user_convertToJSON(login_user_t *login_user);

#endif /* _login_user_H_ */

