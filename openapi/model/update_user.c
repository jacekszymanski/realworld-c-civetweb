#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "update_user.h"



update_user_t *update_user_create(
    char *email,
    char *password,
    char *username,
    char *bio,
    char *image
    ) {
    update_user_t *update_user_local_var = malloc(sizeof(update_user_t));
    if (!update_user_local_var) {
        return NULL;
    }
    update_user_local_var->email = email;
    update_user_local_var->password = password;
    update_user_local_var->username = username;
    update_user_local_var->bio = bio;
    update_user_local_var->image = image;

    return update_user_local_var;
}


void update_user_free(update_user_t *update_user) {
    if(NULL == update_user){
        return ;
    }
    listEntry_t *listEntry;
    if (update_user->email) {
        free(update_user->email);
        update_user->email = NULL;
    }
    if (update_user->password) {
        free(update_user->password);
        update_user->password = NULL;
    }
    if (update_user->username) {
        free(update_user->username);
        update_user->username = NULL;
    }
    if (update_user->bio) {
        free(update_user->bio);
        update_user->bio = NULL;
    }
    if (update_user->image) {
        free(update_user->image);
        update_user->image = NULL;
    }
    free(update_user);
}

cJSON *update_user_convertToJSON(update_user_t *update_user) {
    cJSON *item = cJSON_CreateObject();

    // update_user->email
    if(update_user->email) {
    if(cJSON_AddStringToObject(item, "email", update_user->email) == NULL) {
    goto fail; //String
    }
    }


    // update_user->password
    if(update_user->password) {
    if(cJSON_AddStringToObject(item, "password", update_user->password) == NULL) {
    goto fail; //String
    }
    }


    // update_user->username
    if(update_user->username) {
    if(cJSON_AddStringToObject(item, "username", update_user->username) == NULL) {
    goto fail; //String
    }
    }


    // update_user->bio
    if(update_user->bio) {
    if(cJSON_AddStringToObject(item, "bio", update_user->bio) == NULL) {
    goto fail; //String
    }
    }


    // update_user->image
    if(update_user->image) {
    if(cJSON_AddStringToObject(item, "image", update_user->image) == NULL) {
    goto fail; //String
    }
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

update_user_t *update_user_parseFromJSON(cJSON *update_userJSON){

    update_user_t *update_user_local_var = NULL;

    // update_user->email
    cJSON *email = cJSON_GetObjectItemCaseSensitive(update_userJSON, "email");
    if (email) { 
    if(!cJSON_IsString(email))
    {
    goto end; //String
    }
    }

    // update_user->password
    cJSON *password = cJSON_GetObjectItemCaseSensitive(update_userJSON, "password");
    if (password) { 
    if(!cJSON_IsString(password))
    {
    goto end; //String
    }
    }

    // update_user->username
    cJSON *username = cJSON_GetObjectItemCaseSensitive(update_userJSON, "username");
    if (username) { 
    if(!cJSON_IsString(username))
    {
    goto end; //String
    }
    }

    // update_user->bio
    cJSON *bio = cJSON_GetObjectItemCaseSensitive(update_userJSON, "bio");
    if (bio) { 
    if(!cJSON_IsString(bio))
    {
    goto end; //String
    }
    }

    // update_user->image
    cJSON *image = cJSON_GetObjectItemCaseSensitive(update_userJSON, "image");
    if (image) { 
    if(!cJSON_IsString(image))
    {
    goto end; //String
    }
    }


    update_user_local_var = update_user_create (
        email ? strdup(email->valuestring) : NULL,
        password ? strdup(password->valuestring) : NULL,
        username ? strdup(username->valuestring) : NULL,
        bio ? strdup(bio->valuestring) : NULL,
        image ? strdup(image->valuestring) : NULL
        );

    return update_user_local_var;
end:
    return NULL;

}
