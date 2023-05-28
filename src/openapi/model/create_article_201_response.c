#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "create_article_201_response.h"



create_article_201_response_t *create_article_201_response_create(
    article_t *article
    ) {
    create_article_201_response_t *create_article_201_response_local_var = malloc(sizeof(create_article_201_response_t));
    if (!create_article_201_response_local_var) {
        return NULL;
    }
    create_article_201_response_local_var->article = article;

    return create_article_201_response_local_var;
}


void create_article_201_response_free(create_article_201_response_t *create_article_201_response) {
    if(NULL == create_article_201_response){
        return ;
    }
    listEntry_t *listEntry;
    if (create_article_201_response->article) {
        article_free(create_article_201_response->article);
        create_article_201_response->article = NULL;
    }
    free(create_article_201_response);
}

cJSON *create_article_201_response_convertToJSON(create_article_201_response_t *create_article_201_response) {
    cJSON *item = cJSON_CreateObject();

    // create_article_201_response->article
    if (!create_article_201_response->article) {
        goto fail;
    }
    cJSON *article_local_JSON = article_convertToJSON(create_article_201_response->article);
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

create_article_201_response_t *create_article_201_response_parseFromJSON(cJSON *create_article_201_responseJSON){

    create_article_201_response_t *create_article_201_response_local_var = NULL;

    // define the local variable for create_article_201_response->article
    article_t *article_local_nonprim = NULL;

    // create_article_201_response->article
    cJSON *article = cJSON_GetObjectItemCaseSensitive(create_article_201_responseJSON, "article");
    if (!article) {
        goto end;
    }

    
    article_local_nonprim = article_parseFromJSON(article); //nonprimitive


    create_article_201_response_local_var = create_article_201_response_create (
        article_local_nonprim
        );

    return create_article_201_response_local_var;
end:
    if (article_local_nonprim) {
        article_free(article_local_nonprim);
        article_local_nonprim = NULL;
    }
    return NULL;

}
