/*
 * generic_error_model_errors.h
 *
 * 
 */

#ifndef _generic_error_model_errors_H_
#define _generic_error_model_errors_H_

#include <string.h>
#include <cjson/cJSON.h>
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct generic_error_model_errors_t generic_error_model_errors_t;




typedef struct generic_error_model_errors_t {
    list_t *body; //primitive container

} generic_error_model_errors_t;

generic_error_model_errors_t *generic_error_model_errors_create(
    list_t *body
);

void generic_error_model_errors_free(generic_error_model_errors_t *generic_error_model_errors);

generic_error_model_errors_t *generic_error_model_errors_parseFromJSON(cJSON *generic_error_model_errorsJSON);

cJSON *generic_error_model_errors_convertToJSON(generic_error_model_errors_t *generic_error_model_errors);

#endif /* _generic_error_model_errors_H_ */

