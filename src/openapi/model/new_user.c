#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "new_user.h"



new_user_t *new_user_create(
    char *username,
    char *email,
    char *password
    ) {
    new_user_t *new_user_local_var = malloc(sizeof(new_user_t));
    if (!new_user_local_var) {
        return NULL;
    }
    new_user_local_var->username = username;
    new_user_local_var->email = email;
    new_user_local_var->password = password;

    return new_user_local_var;
}


void new_user_free(new_user_t *new_user) {
    if(NULL == new_user){
        return ;
    }
    listEntry_t *listEntry;
    if (new_user->username) {
        free(new_user->username);
        new_user->username = NULL;
    }
    if (new_user->email) {
        free(new_user->email);
        new_user->email = NULL;
    }
    if (new_user->password) {
        free(new_user->password);
        new_user->password = NULL;
    }
    free(new_user);
}

cJSON *new_user_convertToJSON(new_user_t *new_user) {
    cJSON *item = cJSON_CreateObject();

    // new_user->username
    if (!new_user->username) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "username", new_user->username) == NULL) {
    goto fail; //String
    }


    // new_user->email
    if (!new_user->email) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "email", new_user->email) == NULL) {
    goto fail; //String
    }


    // new_user->password
    if (!new_user->password) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "password", new_user->password) == NULL) {
    goto fail; //String
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

new_user_t *new_user_parseFromJSON(cJSON *new_userJSON){

    new_user_t *new_user_local_var = NULL;

    // new_user->username
    cJSON *username = cJSON_GetObjectItemCaseSensitive(new_userJSON, "username");
    if (!username) {
        goto end;
    }

    
    if(!cJSON_IsString(username))
    {
    goto end; //String
    }

    // new_user->email
    cJSON *email = cJSON_GetObjectItemCaseSensitive(new_userJSON, "email");
    if (!email) {
        goto end;
    }

    
    if(!cJSON_IsString(email))
    {
    goto end; //String
    }

    // new_user->password
    cJSON *password = cJSON_GetObjectItemCaseSensitive(new_userJSON, "password");
    if (!password) {
        goto end;
    }

    
    if(!cJSON_IsString(password))
    {
    goto end; //String
    }


    new_user_local_var = new_user_create (
        strdup(username->valuestring),
        strdup(email->valuestring),
        strdup(password->valuestring)
        );

    return new_user_local_var;
end:
    return NULL;

}
