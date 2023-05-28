#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "create_article_request.h"



create_article_request_t *create_article_request_create(
    new_article_t *article
    ) {
    create_article_request_t *create_article_request_local_var = malloc(sizeof(create_article_request_t));
    if (!create_article_request_local_var) {
        return NULL;
    }
    create_article_request_local_var->article = article;

    return create_article_request_local_var;
}


void create_article_request_free(create_article_request_t *create_article_request) {
    if(NULL == create_article_request){
        return ;
    }
    listEntry_t *listEntry;
    if (create_article_request->article) {
        new_article_free(create_article_request->article);
        create_article_request->article = NULL;
    }
    free(create_article_request);
}

cJSON *create_article_request_convertToJSON(create_article_request_t *create_article_request) {
    cJSON *item = cJSON_CreateObject();

    // create_article_request->article
    if (!create_article_request->article) {
        goto fail;
    }
    cJSON *article_local_JSON = new_article_convertToJSON(create_article_request->article);
    if(article_local_JSON == NULL) {
    goto fail; //model
    }
    cJSON_AddItemToObject(item, "article", article_local_JSON);
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

create_article_request_t *create_article_request_parseFromJSON(cJSON *create_article_requestJSON){

    create_article_request_t *create_article_request_local_var = NULL;

    // define the local variable for create_article_request->article
    new_article_t *article_local_nonprim = NULL;

    // create_article_request->article
    cJSON *article = cJSON_GetObjectItemCaseSensitive(create_article_requestJSON, "article");
    if (!article) {
        goto end;
    }

    
    article_local_nonprim = new_article_parseFromJSON(article); //nonprimitive


    create_article_request_local_var = create_article_request_create (
        article_local_nonprim
        );

    return create_article_request_local_var;
end:
    if (article_local_nonprim) {
        new_article_free(article_local_nonprim);
        article_local_nonprim = NULL;
    }
    return NULL;

}
