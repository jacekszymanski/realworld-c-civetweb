#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "generic_error_model_errors.h"



generic_error_model_errors_t *generic_error_model_errors_create(
    list_t *body
    ) {
    generic_error_model_errors_t *generic_error_model_errors_local_var = malloc(sizeof(generic_error_model_errors_t));
    if (!generic_error_model_errors_local_var) {
        return NULL;
    }
    generic_error_model_errors_local_var->body = body;

    return generic_error_model_errors_local_var;
}


void generic_error_model_errors_free(generic_error_model_errors_t *generic_error_model_errors) {
    if(NULL == generic_error_model_errors){
        return ;
    }
    listEntry_t *listEntry;
    if (generic_error_model_errors->body) {
        list_ForEach(listEntry, generic_error_model_errors->body) {
            free(listEntry->data);
        }
        list_freeList(generic_error_model_errors->body);
        generic_error_model_errors->body = NULL;
    }
    free(generic_error_model_errors);
}

cJSON *generic_error_model_errors_convertToJSON(generic_error_model_errors_t *generic_error_model_errors) {
    cJSON *item = cJSON_CreateObject();

    // generic_error_model_errors->body
    if (!generic_error_model_errors->body) {
        goto fail;
    }
    cJSON *body = cJSON_AddArrayToObject(item, "body");
    if(body == NULL) {
        goto fail; //primitive container
    }

    listEntry_t *bodyListEntry;
    list_ForEach(bodyListEntry, generic_error_model_errors->body) {
    if(cJSON_AddStringToObject(body, "", (char*)bodyListEntry->data) == NULL)
    {
        goto fail;
    }
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

generic_error_model_errors_t *generic_error_model_errors_parseFromJSON(cJSON *generic_error_model_errorsJSON){

    generic_error_model_errors_t *generic_error_model_errors_local_var = NULL;

    // define the local list for generic_error_model_errors->body
    list_t *bodyList = NULL;

    // generic_error_model_errors->body
    cJSON *body = cJSON_GetObjectItemCaseSensitive(generic_error_model_errorsJSON, "body");
    if (!body) {
        goto end;
    }

    
    cJSON *body_local = NULL;
    if(!cJSON_IsArray(body)) {
        goto end;//primitive container
    }
    bodyList = list_createList();

    cJSON_ArrayForEach(body_local, body)
    {
        if(!cJSON_IsString(body_local))
        {
            goto end;
        }
        list_addElement(bodyList , strdup(body_local->valuestring));
    }


    generic_error_model_errors_local_var = generic_error_model_errors_create (
        bodyList
        );

    return generic_error_model_errors_local_var;
end:
    if (bodyList) {
        listEntry_t *listEntry = NULL;
        list_ForEach(listEntry, bodyList) {
            free(listEntry->data);
            listEntry->data = NULL;
        }
        list_freeList(bodyList);
        bodyList = NULL;
    }
    return NULL;

}
