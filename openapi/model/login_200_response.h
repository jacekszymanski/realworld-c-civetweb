/*
 * login_200_response.h
 *
 * 
 */

#ifndef _login_200_response_H_
#define _login_200_response_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct login_200_response_t login_200_response_t;

#include "user.h"



typedef struct login_200_response_t {
    struct user_t *user; //model

} login_200_response_t;

login_200_response_t *login_200_response_create(
    user_t *user
);

void login_200_response_free(login_200_response_t *login_200_response);

login_200_response_t *login_200_response_parseFromJSON(cJSON *login_200_responseJSON);

cJSON *login_200_response_convertToJSON(login_200_response_t *login_200_response);

#endif /* _login_200_response_H_ */

