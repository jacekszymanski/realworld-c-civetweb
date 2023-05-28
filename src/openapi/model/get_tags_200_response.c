#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "get_tags_200_response.h"



get_tags_200_response_t *get_tags_200_response_create(
    list_t *tags
    ) {
    get_tags_200_response_t *get_tags_200_response_local_var = malloc(sizeof(get_tags_200_response_t));
    if (!get_tags_200_response_local_var) {
        return NULL;
    }
    get_tags_200_response_local_var->tags = tags;

    return get_tags_200_response_local_var;
}


void get_tags_200_response_free(get_tags_200_response_t *get_tags_200_response) {
    if(NULL == get_tags_200_response){
        return ;
    }
    listEntry_t *listEntry;
    if (get_tags_200_response->tags) {
        list_ForEach(listEntry, get_tags_200_response->tags) {
            free(listEntry->data);
        }
        list_freeList(get_tags_200_response->tags);
        get_tags_200_response->tags = NULL;
    }
    free(get_tags_200_response);
}

cJSON *get_tags_200_response_convertToJSON(get_tags_200_response_t *get_tags_200_response) {
    cJSON *item = cJSON_CreateObject();

    // get_tags_200_response->tags
    if (!get_tags_200_response->tags) {
        goto fail;
    }
    cJSON *tags = cJSON_AddArrayToObject(item, "tags");
    if(tags == NULL) {
        goto fail; //primitive container
    }

    listEntry_t *tagsListEntry;
    list_ForEach(tagsListEntry, get_tags_200_response->tags) {
    if(cJSON_AddStringToObject(tags, "", (char*)tagsListEntry->data) == NULL)
    {
        goto fail;
    }
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

get_tags_200_response_t *get_tags_200_response_parseFromJSON(cJSON *get_tags_200_responseJSON){

    get_tags_200_response_t *get_tags_200_response_local_var = NULL;

    // define the local list for get_tags_200_response->tags
    list_t *tagsList = NULL;

    // get_tags_200_response->tags
    cJSON *tags = cJSON_GetObjectItemCaseSensitive(get_tags_200_responseJSON, "tags");
    if (!tags) {
        goto end;
    }

    
    cJSON *tags_local = NULL;
    if(!cJSON_IsArray(tags)) {
        goto end;//primitive container
    }
    tagsList = list_createList();

    cJSON_ArrayForEach(tags_local, tags)
    {
        if(!cJSON_IsString(tags_local))
        {
            goto end;
        }
        list_addElement(tagsList , strdup(tags_local->valuestring));
    }


    get_tags_200_response_local_var = get_tags_200_response_create (
        tagsList
        );

    return get_tags_200_response_local_var;
end:
    if (tagsList) {
        listEntry_t *listEntry = NULL;
        list_ForEach(listEntry, tagsList) {
            free(listEntry->data);
            listEntry->data = NULL;
        }
        list_freeList(tagsList);
        tagsList = NULL;
    }
    return NULL;

}
