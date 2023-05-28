#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "new_comment.h"



new_comment_t *new_comment_create(
    char *body
    ) {
    new_comment_t *new_comment_local_var = malloc(sizeof(new_comment_t));
    if (!new_comment_local_var) {
        return NULL;
    }
    new_comment_local_var->body = body;

    return new_comment_local_var;
}


void new_comment_free(new_comment_t *new_comment) {
    if(NULL == new_comment){
        return ;
    }
    listEntry_t *listEntry;
    if (new_comment->body) {
        free(new_comment->body);
        new_comment->body = NULL;
    }
    free(new_comment);
}

cJSON *new_comment_convertToJSON(new_comment_t *new_comment) {
    cJSON *item = cJSON_CreateObject();

    // new_comment->body
    if (!new_comment->body) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "body", new_comment->body) == NULL) {
    goto fail; //String
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

new_comment_t *new_comment_parseFromJSON(cJSON *new_commentJSON){

    new_comment_t *new_comment_local_var = NULL;

    // new_comment->body
    cJSON *body = cJSON_GetObjectItemCaseSensitive(new_commentJSON, "body");
    if (!body) {
        goto end;
    }

    
    if(!cJSON_IsString(body))
    {
    goto end; //String
    }


    new_comment_local_var = new_comment_create (
        strdup(body->valuestring)
        );

    return new_comment_local_var;
end:
    return NULL;

}
