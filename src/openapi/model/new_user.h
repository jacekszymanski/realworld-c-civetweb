/*
 * new_user.h
 *
 * 
 */

#ifndef _new_user_H_
#define _new_user_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct new_user_t new_user_t;




typedef struct new_user_t {
    char *username; // string
    char *email; // string
    char *password; // string

} new_user_t;

new_user_t *new_user_create(
    char *username,
    char *email,
    char *password
);

void new_user_free(new_user_t *new_user);

new_user_t *new_user_parseFromJSON(cJSON *new_userJSON);

cJSON *new_user_convertToJSON(new_user_t *new_user);

#endif /* _new_user_H_ */

