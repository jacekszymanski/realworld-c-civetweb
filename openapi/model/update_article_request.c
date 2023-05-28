#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "update_article_request.h"



update_article_request_t *update_article_request_create(
    update_article_t *article
    ) {
    update_article_request_t *update_article_request_local_var = malloc(sizeof(update_article_request_t));
    if (!update_article_request_local_var) {
        return NULL;
    }
    update_article_request_local_var->article = article;

    return update_article_request_local_var;
}


void update_article_request_free(update_article_request_t *update_article_request) {
    if(NULL == update_article_request){
        return ;
    }
    listEntry_t *listEntry;
    if (update_article_request->article) {
        update_article_free(update_article_request->article);
        update_article_request->article = NULL;
    }
    free(update_article_request);
}

cJSON *update_article_request_convertToJSON(update_article_request_t *update_article_request) {
    cJSON *item = cJSON_CreateObject();

    // update_article_request->article
    if (!update_article_request->article) {
        goto fail;
    }
    cJSON *article_local_JSON = update_article_convertToJSON(update_article_request->article);
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

update_article_request_t *update_article_request_parseFromJSON(cJSON *update_article_requestJSON){

    update_article_request_t *update_article_request_local_var = NULL;

    // define the local variable for update_article_request->article
    update_article_t *article_local_nonprim = NULL;

    // update_article_request->article
    cJSON *article = cJSON_GetObjectItemCaseSensitive(update_article_requestJSON, "article");
    if (!article) {
        goto end;
    }

    
    article_local_nonprim = update_article_parseFromJSON(article); //nonprimitive


    update_article_request_local_var = update_article_request_create (
        article_local_nonprim
        );

    return update_article_request_local_var;
end:
    if (article_local_nonprim) {
        update_article_free(article_local_nonprim);
        article_local_nonprim = NULL;
    }
    return NULL;

}
