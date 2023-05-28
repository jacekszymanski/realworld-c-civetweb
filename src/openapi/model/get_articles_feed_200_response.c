#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "get_articles_feed_200_response.h"



get_articles_feed_200_response_t *get_articles_feed_200_response_create(
    list_t *articles,
    int articles_count
    ) {
    get_articles_feed_200_response_t *get_articles_feed_200_response_local_var = malloc(sizeof(get_articles_feed_200_response_t));
    if (!get_articles_feed_200_response_local_var) {
        return NULL;
    }
    get_articles_feed_200_response_local_var->articles = articles;
    get_articles_feed_200_response_local_var->articles_count = articles_count;

    return get_articles_feed_200_response_local_var;
}


void get_articles_feed_200_response_free(get_articles_feed_200_response_t *get_articles_feed_200_response) {
    if(NULL == get_articles_feed_200_response){
        return ;
    }
    listEntry_t *listEntry;
    if (get_articles_feed_200_response->articles) {
        list_ForEach(listEntry, get_articles_feed_200_response->articles) {
            article_free(listEntry->data);
        }
        list_freeList(get_articles_feed_200_response->articles);
        get_articles_feed_200_response->articles = NULL;
    }
    free(get_articles_feed_200_response);
}

cJSON *get_articles_feed_200_response_convertToJSON(get_articles_feed_200_response_t *get_articles_feed_200_response) {
    cJSON *item = cJSON_CreateObject();

    // get_articles_feed_200_response->articles
    if (!get_articles_feed_200_response->articles) {
        goto fail;
    }
    cJSON *articles = cJSON_AddArrayToObject(item, "articles");
    if(articles == NULL) {
    goto fail; //nonprimitive container
    }

    listEntry_t *articlesListEntry;
    if (get_articles_feed_200_response->articles) {
    list_ForEach(articlesListEntry, get_articles_feed_200_response->articles) {
    cJSON *itemLocal = article_convertToJSON(articlesListEntry->data);
    if(itemLocal == NULL) {
    goto fail;
    }
    cJSON_AddItemToArray(articles, itemLocal);
    }
    }


    // get_articles_feed_200_response->articles_count
    if (!get_articles_feed_200_response->articles_count) {
        goto fail;
    }
    if(cJSON_AddNumberToObject(item, "articlesCount", get_articles_feed_200_response->articles_count) == NULL) {
    goto fail; //Numeric
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

get_articles_feed_200_response_t *get_articles_feed_200_response_parseFromJSON(cJSON *get_articles_feed_200_responseJSON){

    get_articles_feed_200_response_t *get_articles_feed_200_response_local_var = NULL;

    // define the local list for get_articles_feed_200_response->articles
    list_t *articlesList = NULL;

    // get_articles_feed_200_response->articles
    cJSON *articles = cJSON_GetObjectItemCaseSensitive(get_articles_feed_200_responseJSON, "articles");
    if (!articles) {
        goto end;
    }

    
    cJSON *articles_local_nonprimitive = NULL;
    if(!cJSON_IsArray(articles)){
        goto end; //nonprimitive container
    }

    articlesList = list_createList();

    cJSON_ArrayForEach(articles_local_nonprimitive,articles )
    {
        if(!cJSON_IsObject(articles_local_nonprimitive)){
            goto end;
        }
        article_t *articlesItem = article_parseFromJSON(articles_local_nonprimitive);

        list_addElement(articlesList, articlesItem);
    }

    // get_articles_feed_200_response->articles_count
    cJSON *articles_count = cJSON_GetObjectItemCaseSensitive(get_articles_feed_200_responseJSON, "articlesCount");
    if (!articles_count) {
        goto end;
    }

    
    if(!cJSON_IsNumber(articles_count))
    {
    goto end; //Numeric
    }


    get_articles_feed_200_response_local_var = get_articles_feed_200_response_create (
        articlesList,
        articles_count->valuedouble
        );

    return get_articles_feed_200_response_local_var;
end:
    if (articlesList) {
        listEntry_t *listEntry = NULL;
        list_ForEach(listEntry, articlesList) {
            article_free(listEntry->data);
            listEntry->data = NULL;
        }
        list_freeList(articlesList);
        articlesList = NULL;
    }
    return NULL;

}
