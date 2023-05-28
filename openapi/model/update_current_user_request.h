/*
 * update_current_user_request.h
 *
 * 
 */

#ifndef _update_current_user_request_H_
#define _update_current_user_request_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct update_current_user_request_t update_current_user_request_t;

#include "update_user.h"



typedef struct update_current_user_request_t {
    struct update_user_t *user; //model

} update_current_user_request_t;

update_current_user_request_t *update_current_user_request_create(
    update_user_t *user
);

void update_current_user_request_free(update_current_user_request_t *update_current_user_request);

update_current_user_request_t *update_current_user_request_parseFromJSON(cJSON *update_current_user_requestJSON);

cJSON *update_current_user_request_convertToJSON(update_current_user_request_t *update_current_user_request);

#endif /* _update_current_user_request_H_ */

