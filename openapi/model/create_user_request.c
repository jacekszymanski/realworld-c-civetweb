#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "create_user_request.h"



create_user_request_t *create_user_request_create(
    new_user_t *user
    ) {
    create_user_request_t *create_user_request_local_var = malloc(sizeof(create_user_request_t));
    if (!create_user_request_local_var) {
        return NULL;
    }
    create_user_request_local_var->user = user;

    return create_user_request_local_var;
}


void create_user_request_free(create_user_request_t *create_user_request) {
    if(NULL == create_user_request){
        return ;
    }
    listEntry_t *listEntry;
    if (create_user_request->user) {
        new_user_free(create_user_request->user);
        create_user_request->user = NULL;
    }
    free(create_user_request);
}

cJSON *create_user_request_convertToJSON(create_user_request_t *create_user_request) {
    cJSON *item = cJSON_CreateObject();

    // create_user_request->user
    if (!create_user_request->user) {
        goto fail;
    }
    cJSON *user_local_JSON = new_user_convertToJSON(create_user_request->user);
    if(user_local_JSON == NULL) {
    goto fail; //model
    }
    cJSON_AddItemToObject(item, "user", user_local_JSON);
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

create_user_request_t *create_user_request_parseFromJSON(cJSON *create_user_requestJSON){

    create_user_request_t *create_user_request_local_var = NULL;

    // define the local variable for create_user_request->user
    new_user_t *user_local_nonprim = NULL;

    // create_user_request->user
    cJSON *user = cJSON_GetObjectItemCaseSensitive(create_user_requestJSON, "user");
    if (!user) {
        goto end;
    }

    
    user_local_nonprim = new_user_parseFromJSON(user); //nonprimitive


    create_user_request_local_var = create_user_request_create (
        user_local_nonprim
        );

    return create_user_request_local_var;
end:
    if (user_local_nonprim) {
        new_user_free(user_local_nonprim);
        user_local_nonprim = NULL;
    }
    return NULL;

}
