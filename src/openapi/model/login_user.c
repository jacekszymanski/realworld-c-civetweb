#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "login_user.h"



login_user_t *login_user_create(
    char *email,
    char *password
    ) {
    login_user_t *login_user_local_var = malloc(sizeof(login_user_t));
    if (!login_user_local_var) {
        return NULL;
    }
    login_user_local_var->email = email;
    login_user_local_var->password = password;

    return login_user_local_var;
}


void login_user_free(login_user_t *login_user) {
    if(NULL == login_user){
        return ;
    }
    listEntry_t *listEntry;
    if (login_user->email) {
        free(login_user->email);
        login_user->email = NULL;
    }
    if (login_user->password) {
        free(login_user->password);
        login_user->password = NULL;
    }
    free(login_user);
}

cJSON *login_user_convertToJSON(login_user_t *login_user) {
    cJSON *item = cJSON_CreateObject();

    // login_user->email
    if (!login_user->email) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "email", login_user->email) == NULL) {
    goto fail; //String
    }


    // login_user->password
    if (!login_user->password) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "password", login_user->password) == NULL) {
    goto fail; //String
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

login_user_t *login_user_parseFromJSON(cJSON *login_userJSON){

    login_user_t *login_user_local_var = NULL;

    // login_user->email
    cJSON *email = cJSON_GetObjectItemCaseSensitive(login_userJSON, "email");
    if (!email) {
        goto end;
    }

    
    if(!cJSON_IsString(email))
    {
    goto end; //String
    }

    // login_user->password
    cJSON *password = cJSON_GetObjectItemCaseSensitive(login_userJSON, "password");
    if (!password) {
        goto end;
    }

    
    if(!cJSON_IsString(password))
    {
    goto end; //String
    }


    login_user_local_var = login_user_create (
        strdup(email->valuestring),
        strdup(password->valuestring)
        );

    return login_user_local_var;
end:
    return NULL;

}
