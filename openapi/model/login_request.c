#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "login_request.h"



login_request_t *login_request_create(
    login_user_t *user
    ) {
    login_request_t *login_request_local_var = malloc(sizeof(login_request_t));
    if (!login_request_local_var) {
        return NULL;
    }
    login_request_local_var->user = user;

    return login_request_local_var;
}


void login_request_free(login_request_t *login_request) {
    if(NULL == login_request){
        return ;
    }
    listEntry_t *listEntry;
    if (login_request->user) {
        login_user_free(login_request->user);
        login_request->user = NULL;
    }
    free(login_request);
}

cJSON *login_request_convertToJSON(login_request_t *login_request) {
    cJSON *item = cJSON_CreateObject();

    // login_request->user
    if (!login_request->user) {
        goto fail;
    }
    cJSON *user_local_JSON = login_user_convertToJSON(login_request->user);
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

login_request_t *login_request_parseFromJSON(cJSON *login_requestJSON){

    login_request_t *login_request_local_var = NULL;

    // define the local variable for login_request->user
    login_user_t *user_local_nonprim = NULL;

    // login_request->user
    cJSON *user = cJSON_GetObjectItemCaseSensitive(login_requestJSON, "user");
    if (!user) {
        goto end;
    }

    
    user_local_nonprim = login_user_parseFromJSON(user); //nonprimitive


    login_request_local_var = login_request_create (
        user_local_nonprim
        );

    return login_request_local_var;
end:
    if (user_local_nonprim) {
        login_user_free(user_local_nonprim);
        user_local_nonprim = NULL;
    }
    return NULL;

}
