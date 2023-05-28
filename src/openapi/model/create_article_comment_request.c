#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "create_article_comment_request.h"



create_article_comment_request_t *create_article_comment_request_create(
    new_comment_t *comment
    ) {
    create_article_comment_request_t *create_article_comment_request_local_var = malloc(sizeof(create_article_comment_request_t));
    if (!create_article_comment_request_local_var) {
        return NULL;
    }
    create_article_comment_request_local_var->comment = comment;

    return create_article_comment_request_local_var;
}


void create_article_comment_request_free(create_article_comment_request_t *create_article_comment_request) {
    if(NULL == create_article_comment_request){
        return ;
    }
    listEntry_t *listEntry;
    if (create_article_comment_request->comment) {
        new_comment_free(create_article_comment_request->comment);
        create_article_comment_request->comment = NULL;
    }
    free(create_article_comment_request);
}

cJSON *create_article_comment_request_convertToJSON(create_article_comment_request_t *create_article_comment_request) {
    cJSON *item = cJSON_CreateObject();

    // create_article_comment_request->comment
    if (!create_article_comment_request->comment) {
        goto fail;
    }
    cJSON *comment_local_JSON = new_comment_convertToJSON(create_article_comment_request->comment);
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

create_article_comment_request_t *create_article_comment_request_parseFromJSON(cJSON *create_article_comment_requestJSON){

    create_article_comment_request_t *create_article_comment_request_local_var = NULL;

    // define the local variable for create_article_comment_request->comment
    new_comment_t *comment_local_nonprim = NULL;

    // create_article_comment_request->comment
    cJSON *comment = cJSON_GetObjectItemCaseSensitive(create_article_comment_requestJSON, "comment");
    if (!comment) {
        goto end;
    }

    
    comment_local_nonprim = new_comment_parseFromJSON(comment); //nonprimitive


    create_article_comment_request_local_var = create_article_comment_request_create (
        comment_local_nonprim
        );

    return create_article_comment_request_local_var;
end:
    if (comment_local_nonprim) {
        new_comment_free(comment_local_nonprim);
        comment_local_nonprim = NULL;
    }
    return NULL;

}
