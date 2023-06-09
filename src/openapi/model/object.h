/*
 * object.h
 */

#ifndef _object_H_
#define _object_H_

#include <string.h>
#include <cjson/cJSON.h>
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"


typedef struct object_t {
    void *temporary;
} object_t;

object_t *object_create();

void object_free(object_t *object);

object_t *object_parseFromJSON(cJSON *json);

cJSON *object_convertToJSON(object_t *object);

#endif /* _object_H_ */
