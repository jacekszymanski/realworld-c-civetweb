/*
 * create_user_request.h
 *
 * 
 */

#ifndef _create_user_request_H_
#define _create_user_request_H_

#include <string.h>
#include <cjson/cJSON.h>
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct create_user_request_t create_user_request_t;

#include "new_user.h"



typedef struct create_user_request_t {
    struct new_user_t *user; //model

} create_user_request_t;

create_user_request_t *create_user_request_create(
    new_user_t *user
);

void create_user_request_free(create_user_request_t *create_user_request);

create_user_request_t *create_user_request_parseFromJSON(cJSON *create_user_requestJSON);

cJSON *create_user_request_convertToJSON(create_user_request_t *create_user_request);

#endif /* _create_user_request_H_ */

