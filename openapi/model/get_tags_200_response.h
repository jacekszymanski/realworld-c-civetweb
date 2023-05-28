/*
 * get_tags_200_response.h
 *
 * 
 */

#ifndef _get_tags_200_response_H_
#define _get_tags_200_response_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct get_tags_200_response_t get_tags_200_response_t;




typedef struct get_tags_200_response_t {
    list_t *tags; //primitive container

} get_tags_200_response_t;

get_tags_200_response_t *get_tags_200_response_create(
    list_t *tags
);

void get_tags_200_response_free(get_tags_200_response_t *get_tags_200_response);

get_tags_200_response_t *get_tags_200_response_parseFromJSON(cJSON *get_tags_200_responseJSON);

cJSON *get_tags_200_response_convertToJSON(get_tags_200_response_t *get_tags_200_response);

#endif /* _get_tags_200_response_H_ */

