#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "login_200_response.h"



login_200_response_t *login_200_response_create(
    user_t *user
    ) {
    login_200_response_t *login_200_response_local_var = malloc(sizeof(login_200_response_t));
    if (!login_200_response_local_var) {
        return NULL;
    }
    login_200_response_local_var->user = user;

    return login_200_response_local_var;
}


void login_200_response_free(login_200_response_t *login_200_response) {
    if(NULL == login_200_response){
        return ;
    }
    listEntry_t *listEntry;
    if (login_200_response->user) {
        user_free(login_200_response->user);
        login_200_response->user = NULL;
    }
    free(login_200_response);
}

cJSON *login_200_response_convertToJSON(login_200_response_t *login_200_response) {
    cJSON *item = cJSON_CreateObject();

    // login_200_response->user
    if (!login_200_response->user) {
        goto fail;
    }
    cJSON *user_local_JSON = user_convertToJSON(login_200_response->user);
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

login_200_response_t *login_200_response_parseFromJSON(cJSON *login_200_responseJSON){

    login_200_response_t *login_200_response_local_var = NULL;

    // define the local variable for login_200_response->user
    user_t *user_local_nonprim = NULL;

    // login_200_response->user
    cJSON *user = cJSON_GetObjectItemCaseSensitive(login_200_responseJSON, "user");
    if (!user) {
        goto end;
    }

    
    user_local_nonprim = user_parseFromJSON(user); //nonprimitive


    login_200_response_local_var = login_200_response_create (
        user_local_nonprim
        );

    return login_200_response_local_var;
end:
    if (user_local_nonprim) {
        user_free(user_local_nonprim);
        user_local_nonprim = NULL;
    }
    return NULL;

}
