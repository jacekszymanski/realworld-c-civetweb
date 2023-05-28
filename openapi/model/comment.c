#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "comment.h"



comment_t *comment_create(
    int id,
    char *created_at,
    char *updated_at,
    char *body,
    profile_t *author
    ) {
    comment_t *comment_local_var = malloc(sizeof(comment_t));
    if (!comment_local_var) {
        return NULL;
    }
    comment_local_var->id = id;
    comment_local_var->created_at = created_at;
    comment_local_var->updated_at = updated_at;
    comment_local_var->body = body;
    comment_local_var->author = author;

    return comment_local_var;
}


void comment_free(comment_t *comment) {
    if(NULL == comment){
        return ;
    }
    listEntry_t *listEntry;
    if (comment->created_at) {
        free(comment->created_at);
        comment->created_at = NULL;
    }
    if (comment->updated_at) {
        free(comment->updated_at);
        comment->updated_at = NULL;
    }
    if (comment->body) {
        free(comment->body);
        comment->body = NULL;
    }
    if (comment->author) {
        profile_free(comment->author);
        comment->author = NULL;
    }
    free(comment);
}

cJSON *comment_convertToJSON(comment_t *comment) {
    cJSON *item = cJSON_CreateObject();

    // comment->id
    if (!comment->id) {
        goto fail;
    }
    if(cJSON_AddNumberToObject(item, "id", comment->id) == NULL) {
    goto fail; //Numeric
    }


    // comment->created_at
    if (!comment->created_at) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "createdAt", comment->created_at) == NULL) {
    goto fail; //Date-Time
    }


    // comment->updated_at
    if (!comment->updated_at) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "updatedAt", comment->updated_at) == NULL) {
    goto fail; //Date-Time
    }


    // comment->body
    if (!comment->body) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "body", comment->body) == NULL) {
    goto fail; //String
    }


    // comment->author
    if (!comment->author) {
        goto fail;
    }
    cJSON *author_local_JSON = profile_convertToJSON(comment->author);
    if(author_local_JSON == NULL) {
    goto fail; //model
    }
    cJSON_AddItemToObject(item, "author", author_local_JSON);
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

comment_t *comment_parseFromJSON(cJSON *commentJSON){

    comment_t *comment_local_var = NULL;

    // define the local variable for comment->author
    profile_t *author_local_nonprim = NULL;

    // comment->id
    cJSON *id = cJSON_GetObjectItemCaseSensitive(commentJSON, "id");
    if (!id) {
        goto end;
    }

    
    if(!cJSON_IsNumber(id))
    {
    goto end; //Numeric
    }

    // comment->created_at
    cJSON *created_at = cJSON_GetObjectItemCaseSensitive(commentJSON, "createdAt");
    if (!created_at) {
        goto end;
    }

    
    if(!cJSON_IsString(created_at))
    {
    goto end; //DateTime
    }

    // comment->updated_at
    cJSON *updated_at = cJSON_GetObjectItemCaseSensitive(commentJSON, "updatedAt");
    if (!updated_at) {
        goto end;
    }

    
    if(!cJSON_IsString(updated_at))
    {
    goto end; //DateTime
    }

    // comment->body
    cJSON *body = cJSON_GetObjectItemCaseSensitive(commentJSON, "body");
    if (!body) {
        goto end;
    }

    
    if(!cJSON_IsString(body))
    {
    goto end; //String
    }

    // comment->author
    cJSON *author = cJSON_GetObjectItemCaseSensitive(commentJSON, "author");
    if (!author) {
        goto end;
    }

    
    author_local_nonprim = profile_parseFromJSON(author); //nonprimitive


    comment_local_var = comment_create (
        id->valuedouble,
        strdup(created_at->valuestring),
        strdup(updated_at->valuestring),
        strdup(body->valuestring),
        author_local_nonprim
        );

    return comment_local_var;
end:
    if (author_local_nonprim) {
        profile_free(author_local_nonprim);
        author_local_nonprim = NULL;
    }
    return NULL;

}
