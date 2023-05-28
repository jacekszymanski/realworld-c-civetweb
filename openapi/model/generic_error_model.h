/*
 * generic_error_model.h
 *
 * 
 */

#ifndef _generic_error_model_H_
#define _generic_error_model_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct generic_error_model_t generic_error_model_t;

#include "generic_error_model_errors.h"



typedef struct generic_error_model_t {
    struct generic_error_model_errors_t *errors; //model

} generic_error_model_t;

generic_error_model_t *generic_error_model_create(
    generic_error_model_errors_t *errors
);

void generic_error_model_free(generic_error_model_t *generic_error_model);

generic_error_model_t *generic_error_model_parseFromJSON(cJSON *generic_error_modelJSON);

cJSON *generic_error_model_convertToJSON(generic_error_model_t *generic_error_model);

#endif /* _generic_error_model_H_ */

