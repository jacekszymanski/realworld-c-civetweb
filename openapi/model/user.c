#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "user.h"



user_t *user_create(
    char *email,
    char *token,
    char *username,
    char *bio,
    char *image
    ) {
    user_t *user_local_var = malloc(sizeof(user_t));
    if (!user_local_var) {
        return NULL;
    }
    user_local_var->email = email;
    user_local_var->token = token;
    user_local_var->username = username;
    user_local_var->bio = bio;
    user_local_var->image = image;

    return user_local_var;
}


void user_free(user_t *user) {
    if(NULL == user){
        return ;
    }
    listEntry_t *listEntry;
    if (user->email) {
        free(user->email);
        user->email = NULL;
    }
    if (user->token) {
        free(user->token);
        user->token = NULL;
    }
    if (user->username) {
        free(user->username);
        user->username = NULL;
    }
    if (user->bio) {
        free(user->bio);
        user->bio = NULL;
    }
    if (user->image) {
        free(user->image);
        user->image = NULL;
    }
    free(user);
}

cJSON *user_convertToJSON(user_t *user) {
    cJSON *item = cJSON_CreateObject();

    // user->email
    if (!user->email) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "email", user->email) == NULL) {
    goto fail; //String
    }


    // user->token
    if (!user->token) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "token", user->token) == NULL) {
    goto fail; //String
    }


    // user->username
    if (!user->username) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "username", user->username) == NULL) {
    goto fail; //String
    }


    // user->bio
    if (!user->bio) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "bio", user->bio) == NULL) {
    goto fail; //String
    }


    // user->image
    if (!user->image) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "image", user->image) == NULL) {
    goto fail; //String
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

user_t *user_parseFromJSON(cJSON *userJSON){

    user_t *user_local_var = NULL;

    // user->email
    cJSON *email = cJSON_GetObjectItemCaseSensitive(userJSON, "email");
    if (!email) {
        goto end;
    }

    
    if(!cJSON_IsString(email))
    {
    goto end; //String
    }

    // user->token
    cJSON *token = cJSON_GetObjectItemCaseSensitive(userJSON, "token");
    if (!token) {
        goto end;
    }

    
    if(!cJSON_IsString(token))
    {
    goto end; //String
    }

    // user->username
    cJSON *username = cJSON_GetObjectItemCaseSensitive(userJSON, "username");
    if (!username) {
        goto end;
    }

    
    if(!cJSON_IsString(username))
    {
    goto end; //String
    }

    // user->bio
    cJSON *bio = cJSON_GetObjectItemCaseSensitive(userJSON, "bio");
    if (!bio) {
        goto end;
    }

    
    if(!cJSON_IsString(bio))
    {
    goto end; //String
    }

    // user->image
    cJSON *image = cJSON_GetObjectItemCaseSensitive(userJSON, "image");
    if (!image) {
        goto end;
    }

    
    if(!cJSON_IsString(image))
    {
    goto end; //String
    }


    user_local_var = user_create (
        strdup(email->valuestring),
        strdup(token->valuestring),
        strdup(username->valuestring),
        strdup(bio->valuestring),
        strdup(image->valuestring)
        );

    return user_local_var;
end:
    return NULL;

}
