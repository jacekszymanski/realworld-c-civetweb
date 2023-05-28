#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "get_article_comments_200_response.h"



get_article_comments_200_response_t *get_article_comments_200_response_create(
    list_t *comments
    ) {
    get_article_comments_200_response_t *get_article_comments_200_response_local_var = malloc(sizeof(get_article_comments_200_response_t));
    if (!get_article_comments_200_response_local_var) {
        return NULL;
    }
    get_article_comments_200_response_local_var->comments = comments;

    return get_article_comments_200_response_local_var;
}


void get_article_comments_200_response_free(get_article_comments_200_response_t *get_article_comments_200_response) {
    if(NULL == get_article_comments_200_response){
        return ;
    }
    listEntry_t *listEntry;
    if (get_article_comments_200_response->comments) {
        list_ForEach(listEntry, get_article_comments_200_response->comments) {
            comment_free(listEntry->data);
        }
        list_freeList(get_article_comments_200_response->comments);
        get_article_comments_200_response->comments = NULL;
    }
    free(get_article_comments_200_response);
}

cJSON *get_article_comments_200_response_convertToJSON(get_article_comments_200_response_t *get_article_comments_200_response) {
    cJSON *item = cJSON_CreateObject();

    // get_article_comments_200_response->comments
    if (!get_article_comments_200_response->comments) {
        goto fail;
    }
    cJSON *comments = cJSON_AddArrayToObject(item, "comments");
    if(comments == NULL) {
    goto fail; //nonprimitive container
    }

    listEntry_t *commentsListEntry;
    if (get_article_comments_200_response->comments) {
    list_ForEach(commentsListEntry, get_article_comments_200_response->comments) {
    cJSON *itemLocal = comment_convertToJSON(commentsListEntry->data);
    if(itemLocal == NULL) {
    goto fail;
    }
    cJSON_AddItemToArray(comments, itemLocal);
    }
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

get_article_comments_200_response_t *get_article_comments_200_response_parseFromJSON(cJSON *get_article_comments_200_responseJSON){

    get_article_comments_200_response_t *get_article_comments_200_response_local_var = NULL;

    // define the local list for get_article_comments_200_response->comments
    list_t *commentsList = NULL;

    // get_article_comments_200_response->comments
    cJSON *comments = cJSON_GetObjectItemCaseSensitive(get_article_comments_200_responseJSON, "comments");
    if (!comments) {
        goto end;
    }

    
    cJSON *comments_local_nonprimitive = NULL;
    if(!cJSON_IsArray(comments)){
        goto end; //nonprimitive container
    }

    commentsList = list_createList();

    cJSON_ArrayForEach(comments_local_nonprimitive,comments )
    {
        if(!cJSON_IsObject(comments_local_nonprimitive)){
            goto end;
        }
        comment_t *commentsItem = comment_parseFromJSON(comments_local_nonprimitive);

        list_addElement(commentsList, commentsItem);
    }


    get_article_comments_200_response_local_var = get_article_comments_200_response_create (
        commentsList
        );

    return get_article_comments_200_response_local_var;
end:
    if (commentsList) {
        listEntry_t *listEntry = NULL;
        list_ForEach(listEntry, commentsList) {
            comment_free(listEntry->data);
            listEntry->data = NULL;
        }
        list_freeList(commentsList);
        commentsList = NULL;
    }
    return NULL;

}
