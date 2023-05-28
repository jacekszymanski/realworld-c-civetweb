#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "create_article_comment_200_response.h"



create_article_comment_200_response_t *create_article_comment_200_response_create(
    comment_t *comment
    ) {
    create_article_comment_200_response_t *create_article_comment_200_response_local_var = malloc(sizeof(create_article_comment_200_response_t));
    if (!create_article_comment_200_response_local_var) {
        return NULL;
    }
    create_article_comment_200_response_local_var->comment = comment;

    return create_article_comment_200_response_local_var;
}


void create_article_comment_200_response_free(create_article_comment_200_response_t *create_article_comment_200_response) {
    if(NULL == create_article_comment_200_response){
        return ;
    }
    listEntry_t *listEntry;
    if (create_article_comment_200_response->comment) {
        comment_free(create_article_comment_200_response->comment);
        create_article_comment_200_response->comment = NULL;
    }
    free(create_article_comment_200_response);
}

cJSON *create_article_comment_200_response_convertToJSON(create_article_comment_200_response_t *create_article_comment_200_response) {
    cJSON *item = cJSON_CreateObject();

    // create_article_comment_200_response->comment
    if (!create_article_comment_200_response->comment) {
        goto fail;
    }
    cJSON *comment_local_JSON = comment_convertToJSON(create_article_comment_200_response->comment);
    if(comment_local_JSON == NULL) {
    goto fail; //model
    }
    cJSON_AddItemToObject(item, "comment", comment_local_JSON);
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

create_article_comment_200_response_t *create_article_comment_200_response_parseFromJSON(cJSON *create_article_comment_200_responseJSON){

    create_article_comment_200_response_t *create_article_comment_200_response_local_var = NULL;

    // define the local variable for create_article_comment_200_response->comment
    comment_t *comment_local_nonprim = NULL;

    // create_article_comment_200_response->comment
    cJSON *comment = cJSON_GetObjectItemCaseSensitive(create_article_comment_200_responseJSON, "comment");
    if (!comment) {
        goto end;
    }

    
    comment_local_nonprim = comment_parseFromJSON(comment); //nonprimitive


    create_article_comment_200_response_local_var = create_article_comment_200_response_create (
        comment_local_nonprim
        );

    return create_article_comment_200_response_local_var;
end:
    if (comment_local_nonprim) {
        comment_free(comment_local_nonprim);
        comment_local_nonprim = NULL;
    }
    return NULL;

}
