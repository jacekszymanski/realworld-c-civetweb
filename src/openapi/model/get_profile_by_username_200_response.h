/*
 * get_profile_by_username_200_response.h
 *
 * 
 */

#ifndef _get_profile_by_username_200_response_H_
#define _get_profile_by_username_200_response_H_

#include <string.h>
#include <cjson/cJSON.h>
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct get_profile_by_username_200_response_t get_profile_by_username_200_response_t;

#include "profile.h"



typedef struct get_profile_by_username_200_response_t {
    struct profile_t *profile; //model

} get_profile_by_username_200_response_t;

get_profile_by_username_200_response_t *get_profile_by_username_200_response_create(
    profile_t *profile
);

void get_profile_by_username_200_response_free(get_profile_by_username_200_response_t *get_profile_by_username_200_response);

get_profile_by_username_200_response_t *get_profile_by_username_200_response_parseFromJSON(cJSON *get_profile_by_username_200_responseJSON);

cJSON *get_profile_by_username_200_response_convertToJSON(get_profile_by_username_200_response_t *get_profile_by_username_200_response);

#endif /* _get_profile_by_username_200_response_H_ */

