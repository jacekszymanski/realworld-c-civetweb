#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "new_article.h"



new_article_t *new_article_create(
    char *title,
    char *description,
    char *body,
    list_t *tag_list
    ) {
    new_article_t *new_article_local_var = malloc(sizeof(new_article_t));
    if (!new_article_local_var) {
        return NULL;
    }
    new_article_local_var->title = title;
    new_article_local_var->description = description;
    new_article_local_var->body = body;
    new_article_local_var->tag_list = tag_list;

    return new_article_local_var;
}


void new_article_free(new_article_t *new_article) {
    if(NULL == new_article){
        return ;
    }
    listEntry_t *listEntry;
    if (new_article->title) {
        free(new_article->title);
        new_article->title = NULL;
    }
    if (new_article->description) {
        free(new_article->description);
        new_article->description = NULL;
    }
    if (new_article->body) {
        free(new_article->body);
        new_article->body = NULL;
    }
    if (new_article->tag_list) {
        list_ForEach(listEntry, new_article->tag_list) {
            free(listEntry->data);
        }
        list_freeList(new_article->tag_list);
        new_article->tag_list = NULL;
    }
    free(new_article);
}

cJSON *new_article_convertToJSON(new_article_t *new_article) {
    cJSON *item = cJSON_CreateObject();

    // new_article->title
    if (!new_article->title) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "title", new_article->title) == NULL) {
    goto fail; //String
    }


    // new_article->description
    if (!new_article->description) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "description", new_article->description) == NULL) {
    goto fail; //String
    }


    // new_article->body
    if (!new_article->body) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "body", new_article->body) == NULL) {
    goto fail; //String
    }


    // new_article->tag_list
    if(new_article->tag_list) {
    cJSON *tag_list = cJSON_AddArrayToObject(item, "tagList");
    if(tag_list == NULL) {
        goto fail; //primitive container
    }

    listEntry_t *tag_listListEntry;
    list_ForEach(tag_listListEntry, new_article->tag_list) {
    if(cJSON_AddStringToObject(tag_list, "", (char*)tag_listListEntry->data) == NULL)
    {
        goto fail;
    }
    }
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

new_article_t *new_article_parseFromJSON(cJSON *new_articleJSON){

    new_article_t *new_article_local_var = NULL;

    // define the local list for new_article->tag_list
    list_t *tag_listList = NULL;

    // new_article->title
    cJSON *title = cJSON_GetObjectItemCaseSensitive(new_articleJSON, "title");
    if (!title) {
        goto end;
    }

    
    if(!cJSON_IsString(title))
    {
    goto end; //String
    }

    // new_article->description
    cJSON *description = cJSON_GetObjectItemCaseSensitive(new_articleJSON, "description");
    if (!description) {
        goto end;
    }

    
    if(!cJSON_IsString(description))
    {
    goto end; //String
    }

    // new_article->body
    cJSON *body = cJSON_GetObjectItemCaseSensitive(new_articleJSON, "body");
    if (!body) {
        goto end;
    }

    
    if(!cJSON_IsString(body))
    {
    goto end; //String
    }

    // new_article->tag_list
    cJSON *tag_list = cJSON_GetObjectItemCaseSensitive(new_articleJSON, "tagList");
    if (tag_list) { 
    cJSON *tag_list_local = NULL;
    if(!cJSON_IsArray(tag_list)) {
        goto end;//primitive container
    }
    tag_listList = list_createList();

    cJSON_ArrayForEach(tag_list_local, tag_list)
    {
        if(!cJSON_IsString(tag_list_local))
        {
            goto end;
        }
        list_addElement(tag_listList , strdup(tag_list_local->valuestring));
    }
    }


    new_article_local_var = new_article_create (
        strdup(title->valuestring),
        strdup(description->valuestring),
        strdup(body->valuestring),
        tag_list ? tag_listList : NULL
        );

    return new_article_local_var;
end:
    if (tag_listList) {
        listEntry_t *listEntry = NULL;
        list_ForEach(listEntry, tag_listList) {
            free(listEntry->data);
            listEntry->data = NULL;
        }
        list_freeList(tag_listList);
        tag_listList = NULL;
    }
    return NULL;

}
