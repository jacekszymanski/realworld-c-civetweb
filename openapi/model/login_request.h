/*
 * login_request.h
 *
 * 
 */

#ifndef _login_request_H_
#define _login_request_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct login_request_t login_request_t;

#include "login_user.h"



typedef struct login_request_t {
    struct login_user_t *user; //model

} login_request_t;

login_request_t *login_request_create(
    login_user_t *user
);

void login_request_free(login_request_t *login_request);

login_request_t *login_request_parseFromJSON(cJSON *login_requestJSON);

cJSON *login_request_convertToJSON(login_request_t *login_request);

#endif /* _login_request_H_ */

