/*
 * update_user.h
 *
 * 
 */

#ifndef _update_user_H_
#define _update_user_H_

#include <string.h>
#include <cjson/cJSON.h>
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct update_user_t update_user_t;




typedef struct update_user_t {
    char *email; // string
    char *password; // string
    char *username; // string
    char *bio; // string
    char *image; // string

} update_user_t;

update_user_t *update_user_create(
    char *email,
    char *password,
    char *username,
    char *bio,
    char *image
);

void update_user_free(update_user_t *update_user);

update_user_t *update_user_parseFromJSON(cJSON *update_userJSON);

cJSON *update_user_convertToJSON(update_user_t *update_user);

#endif /* _update_user_H_ */

