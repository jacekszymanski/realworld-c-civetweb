#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "update_article.h"



update_article_t *update_article_create(
    char *title,
    char *description,
    char *body
    ) {
    update_article_t *update_article_local_var = malloc(sizeof(update_article_t));
    if (!update_article_local_var) {
        return NULL;
    }
    update_article_local_var->title = title;
    update_article_local_var->description = description;
    update_article_local_var->body = body;

    return update_article_local_var;
}


void update_article_free(update_article_t *update_article) {
    if(NULL == update_article){
        return ;
    }
    listEntry_t *listEntry;
    if (update_article->title) {
        free(update_article->title);
        update_article->title = NULL;
    }
    if (update_article->description) {
        free(update_article->description);
        update_article->description = NULL;
    }
    if (update_article->body) {
        free(update_article->body);
        update_article->body = NULL;
    }
    free(update_article);
}

cJSON *update_article_convertToJSON(update_article_t *update_article) {
    cJSON *item = cJSON_CreateObject();

    // update_article->title
    if(update_article->title) {
    if(cJSON_AddStringToObject(item, "title", update_article->title) == NULL) {
    goto fail; //String
    }
    }


    // update_article->description
    if(update_article->description) {
    if(cJSON_AddStringToObject(item, "description", update_article->description) == NULL) {
    goto fail; //String
    }
    }


    // update_article->body
    if(update_article->body) {
    if(cJSON_AddStringToObject(item, "body", update_article->body) == NULL) {
    goto fail; //String
    }
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

update_article_t *update_article_parseFromJSON(cJSON *update_articleJSON){

    update_article_t *update_article_local_var = NULL;

    // update_article->title
    cJSON *title = cJSON_GetObjectItemCaseSensitive(update_articleJSON, "title");
    if (title) { 
    if(!cJSON_IsString(title))
    {
    goto end; //String
    }
    }

    // update_article->description
    cJSON *description = cJSON_GetObjectItemCaseSensitive(update_articleJSON, "description");
    if (description) { 
    if(!cJSON_IsString(description))
    {
    goto end; //String
    }
    }

    // update_article->body
    cJSON *body = cJSON_GetObjectItemCaseSensitive(update_articleJSON, "body");
    if (body) { 
    if(!cJSON_IsString(body))
    {
    goto end; //String
    }
    }


    update_article_local_var = update_article_create (
        title ? strdup(title->valuestring) : NULL,
        description ? strdup(description->valuestring) : NULL,
        body ? strdup(body->valuestring) : NULL
        );

    return update_article_local_var;
end:
    return NULL;

}
