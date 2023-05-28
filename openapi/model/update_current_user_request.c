#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "update_current_user_request.h"



update_current_user_request_t *update_current_user_request_create(
    update_user_t *user
    ) {
    update_current_user_request_t *update_current_user_request_local_var = malloc(sizeof(update_current_user_request_t));
    if (!update_current_user_request_local_var) {
        return NULL;
    }
    update_current_user_request_local_var->user = user;

    return update_current_user_request_local_var;
}


void update_current_user_request_free(update_current_user_request_t *update_current_user_request) {
    if(NULL == update_current_user_request){
        return ;
    }
    listEntry_t *listEntry;
    if (update_current_user_request->user) {
        update_user_free(update_current_user_request->user);
        update_current_user_request->user = NULL;
    }
    free(update_current_user_request);
}

cJSON *update_current_user_request_convertToJSON(update_current_user_request_t *update_current_user_request) {
    cJSON *item = cJSON_CreateObject();

    // update_current_user_request->user
    if (!update_current_user_request->user) {
        goto fail;
    }
    cJSON *user_local_JSON = update_user_convertToJSON(update_current_user_request->user);
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

update_current_user_request_t *update_current_user_request_parseFromJSON(cJSON *update_current_user_requestJSON){

    update_current_user_request_t *update_current_user_request_local_var = NULL;

    // define the local variable for update_current_user_request->user
    update_user_t *user_local_nonprim = NULL;

    // update_current_user_request->user
    cJSON *user = cJSON_GetObjectItemCaseSensitive(update_current_user_requestJSON, "user");
    if (!user) {
        goto end;
    }

    
    user_local_nonprim = update_user_parseFromJSON(user); //nonprimitive


    update_current_user_request_local_var = update_current_user_request_create (
        user_local_nonprim
        );

    return update_current_user_request_local_var;
end:
    if (user_local_nonprim) {
        update_user_free(user_local_nonprim);
        user_local_nonprim = NULL;
    }
    return NULL;

}
