#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "generic_error_model.h"



generic_error_model_t *generic_error_model_create(
    generic_error_model_errors_t *errors
    ) {
    generic_error_model_t *generic_error_model_local_var = malloc(sizeof(generic_error_model_t));
    if (!generic_error_model_local_var) {
        return NULL;
    }
    generic_error_model_local_var->errors = errors;

    return generic_error_model_local_var;
}


void generic_error_model_free(generic_error_model_t *generic_error_model) {
    if(NULL == generic_error_model){
        return ;
    }
    listEntry_t *listEntry;
    if (generic_error_model->errors) {
        generic_error_model_errors_free(generic_error_model->errors);
        generic_error_model->errors = NULL;
    }
    free(generic_error_model);
}

cJSON *generic_error_model_convertToJSON(generic_error_model_t *generic_error_model) {
    cJSON *item = cJSON_CreateObject();

    // generic_error_model->errors
    if (!generic_error_model->errors) {
        goto fail;
    }
    cJSON *errors_local_JSON = generic_error_model_errors_convertToJSON(generic_error_model->errors);
    if(errors_local_JSON == NULL) {
    goto fail; //model
    }
    cJSON_AddItemToObject(item, "errors", errors_local_JSON);
    if(item->child == NULL) {
    goto fail;
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

generic_error_model_t *generic_error_model_parseFromJSON(cJSON *generic_error_modelJSON){

    generic_error_model_t *generic_error_model_local_var = NULL;

    // define the local variable for generic_error_model->errors
    generic_error_model_errors_t *errors_local_nonprim = NULL;

    // generic_error_model->errors
    cJSON *errors = cJSON_GetObjectItemCaseSensitive(generic_error_modelJSON, "errors");
    if (!errors) {
        goto end;
    }

    
    errors_local_nonprim = generic_error_model_errors_parseFromJSON(errors); //nonprimitive


    generic_error_model_local_var = generic_error_model_create (
        errors_local_nonprim
        );

    return generic_error_model_local_var;
end:
    if (errors_local_nonprim) {
        generic_error_model_errors_free(errors_local_nonprim);
        errors_local_nonprim = NULL;
    }
    return NULL;

}
