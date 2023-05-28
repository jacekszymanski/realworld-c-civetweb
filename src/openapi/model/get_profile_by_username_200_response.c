#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "get_profile_by_username_200_response.h"



get_profile_by_username_200_response_t *get_profile_by_username_200_response_create(
    profile_t *profile
    ) {
    get_profile_by_username_200_response_t *get_profile_by_username_200_response_local_var = malloc(sizeof(get_profile_by_username_200_response_t));
    if (!get_profile_by_username_200_response_local_var) {
        return NULL;
    }
    get_profile_by_username_200_response_local_var->profile = profile;

    return get_profile_by_username_200_response_local_var;
}


void get_profile_by_username_200_response_free(get_profile_by_username_200_response_t *get_profile_by_username_200_response) {
    if(NULL == get_profile_by_username_200_response){
        return ;
    }
    listEntry_t *listEntry;
    if (get_profile_by_username_200_response->profile) {
        profile_free(get_profile_by_username_200_response->profile);
        get_profile_by_username_200_response->profile = NULL;
    }
    free(get_profile_by_username_200_response);
}

cJSON *get_profile_by_username_200_response_convertToJSON(get_profile_by_username_200_response_t *get_profile_by_username_200_response) {
    cJSON *item = cJSON_CreateObject();

    // get_profile_by_username_200_response->profile
    if (!get_profile_by_username_200_response->profile) {
        goto fail;
    }
    cJSON *profile_local_JSON = profile_convertToJSON(get_profile_by_username_200_response->profile);
    if(profile_local_JSON == NULL) {
    goto fail; //model
    }
    cJSON_AddItemToObject(item, "profile", profile_local_JSON);
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

get_profile_by_username_200_response_t *get_profile_by_username_200_response_parseFromJSON(cJSON *get_profile_by_username_200_responseJSON){

    get_profile_by_username_200_response_t *get_profile_by_username_200_response_local_var = NULL;

    // define the local variable for get_profile_by_username_200_response->profile
    profile_t *profile_local_nonprim = NULL;

    // get_profile_by_username_200_response->profile
    cJSON *profile = cJSON_GetObjectItemCaseSensitive(get_profile_by_username_200_responseJSON, "profile");
    if (!profile) {
        goto end;
    }

    
    profile_local_nonprim = profile_parseFromJSON(profile); //nonprimitive


    get_profile_by_username_200_response_local_var = get_profile_by_username_200_response_create (
        profile_local_nonprim
        );

    return get_profile_by_username_200_response_local_var;
end:
    if (profile_local_nonprim) {
        profile_free(profile_local_nonprim);
        profile_local_nonprim = NULL;
    }
    return NULL;

}
