#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "profile.h"



profile_t *profile_create(
    char *username,
    char *bio,
    char *image,
    int following
    ) {
    profile_t *profile_local_var = malloc(sizeof(profile_t));
    if (!profile_local_var) {
        return NULL;
    }
    profile_local_var->username = username;
    profile_local_var->bio = bio;
    profile_local_var->image = image;
    profile_local_var->following = following;

    return profile_local_var;
}


void profile_free(profile_t *profile) {
    if(NULL == profile){
        return ;
    }
    listEntry_t *listEntry;
    if (profile->username) {
        free(profile->username);
        profile->username = NULL;
    }
    if (profile->bio) {
        free(profile->bio);
        profile->bio = NULL;
    }
    if (profile->image) {
        free(profile->image);
        profile->image = NULL;
    }
    free(profile);
}

cJSON *profile_convertToJSON(profile_t *profile) {
    cJSON *item = cJSON_CreateObject();

    // profile->username
    if (!profile->username) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "username", profile->username) == NULL) {
    goto fail; //String
    }


    // profile->bio
    if (!profile->bio) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "bio", profile->bio) == NULL) {
    goto fail; //String
    }


    // profile->image
    if (!profile->image) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "image", profile->image) == NULL) {
    goto fail; //String
    }


    if(cJSON_AddBoolToObject(item, "following", profile->following) == NULL) {
    goto fail; //Bool
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

profile_t *profile_parseFromJSON(cJSON *profileJSON){

    profile_t *profile_local_var = NULL;

    // profile->username
    cJSON *username = cJSON_GetObjectItemCaseSensitive(profileJSON, "username");
    if (!username) {
        goto end;
    }


    if(!cJSON_IsString(username))
    {
    goto end; //String
    }

    // profile->bio
    cJSON *bio = cJSON_GetObjectItemCaseSensitive(profileJSON, "bio");
    if (!bio) {
        goto end;
    }


    if(!cJSON_IsString(bio))
    {
    goto end; //String
    }

    // profile->image
    cJSON *image = cJSON_GetObjectItemCaseSensitive(profileJSON, "image");
    if (!image) {
        goto end;
    }


    if(!cJSON_IsString(image))
    {
    goto end; //String
    }

    // profile->following
    cJSON *following = cJSON_GetObjectItemCaseSensitive(profileJSON, "following");
    if (!following) {
        goto end;
    }


    if(!cJSON_IsBool(following))
    {
    goto end; //Bool
    }


    profile_local_var = profile_create (
        strdup(username->valuestring),
        strdup(bio->valuestring),
        strdup(image->valuestring),
        following->valueint
        );

    return profile_local_var;
end:
    return NULL;

}
