#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "article.h"



article_t *article_create(
    char *slug,
    char *title,
    char *description,
    char *body,
    list_t *tag_list,
    char *created_at,
    char *updated_at,
    int favorited,
    int favorites_count,
    profile_t *author
    ) {
    article_t *article_local_var = malloc(sizeof(article_t));
    if (!article_local_var) {
        return NULL;
    }
    article_local_var->slug = slug;
    article_local_var->title = title;
    article_local_var->description = description;
    article_local_var->body = body;
    article_local_var->tag_list = tag_list;
    article_local_var->created_at = created_at;
    article_local_var->updated_at = updated_at;
    article_local_var->favorited = favorited;
    article_local_var->favorites_count = favorites_count;
    article_local_var->author = author;

    return article_local_var;
}


void article_free(article_t *article) {
    if(NULL == article){
        return ;
    }
    listEntry_t *listEntry;
    if (article->slug) {
        free(article->slug);
        article->slug = NULL;
    }
    if (article->title) {
        free(article->title);
        article->title = NULL;
    }
    if (article->description) {
        free(article->description);
        article->description = NULL;
    }
    if (article->body) {
        free(article->body);
        article->body = NULL;
    }
    if (article->tag_list) {
        list_ForEach(listEntry, article->tag_list) {
            free(listEntry->data);
        }
        list_freeList(article->tag_list);
        article->tag_list = NULL;
    }
    if (article->created_at) {
        free(article->created_at);
        article->created_at = NULL;
    }
    if (article->updated_at) {
        free(article->updated_at);
        article->updated_at = NULL;
    }
    if (article->author) {
        profile_free(article->author);
        article->author = NULL;
    }
    free(article);
}

cJSON *article_convertToJSON(article_t *article) {
    cJSON *item = cJSON_CreateObject();

    // article->slug
    if (!article->slug) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "slug", article->slug) == NULL) {
    goto fail; //String
    }


    // article->title
    if (!article->title) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "title", article->title) == NULL) {
    goto fail; //String
    }


    // article->description
    if (!article->description) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "description", article->description) == NULL) {
    goto fail; //String
    }


    // article->body
    if (!article->body) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "body", article->body) == NULL) {
    goto fail; //String
    }


    // article->tag_list
    if (!article->tag_list) {
        goto fail;
    }
    cJSON *tag_list = cJSON_AddArrayToObject(item, "tagList");
    if(tag_list == NULL) {
        goto fail; //primitive container
    }

    listEntry_t *tag_listListEntry;
    list_ForEach(tag_listListEntry, article->tag_list) {
    if(cJSON_AddStringToObject(tag_list, "", (char*)tag_listListEntry->data) == NULL)
    {
        goto fail;
    }
    }


    // article->created_at
    if (!article->created_at) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "createdAt", article->created_at) == NULL) {
    goto fail; //Date-Time
    }


    // article->updated_at
    if (!article->updated_at) {
        goto fail;
    }
    if(cJSON_AddStringToObject(item, "updatedAt", article->updated_at) == NULL) {
    goto fail; //Date-Time
    }


    // article->favorited
    if (!article->favorited) {
        goto fail;
    }
    if(cJSON_AddBoolToObject(item, "favorited", article->favorited) == NULL) {
    goto fail; //Bool
    }


    // article->favorites_count
    if (!article->favorites_count) {
        goto fail;
    }
    if(cJSON_AddNumberToObject(item, "favoritesCount", article->favorites_count) == NULL) {
    goto fail; //Numeric
    }


    // article->author
    if (!article->author) {
        goto fail;
    }
    cJSON *author_local_JSON = profile_convertToJSON(article->author);
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

article_t *article_parseFromJSON(cJSON *articleJSON){

    article_t *article_local_var = NULL;

    // define the local list for article->tag_list
    list_t *tag_listList = NULL;

    // define the local variable for article->author
    profile_t *author_local_nonprim = NULL;

    // article->slug
    cJSON *slug = cJSON_GetObjectItemCaseSensitive(articleJSON, "slug");
    if (!slug) {
        goto end;
    }

    
    if(!cJSON_IsString(slug))
    {
    goto end; //String
    }

    // article->title
    cJSON *title = cJSON_GetObjectItemCaseSensitive(articleJSON, "title");
    if (!title) {
        goto end;
    }

    
    if(!cJSON_IsString(title))
    {
    goto end; //String
    }

    // article->description
    cJSON *description = cJSON_GetObjectItemCaseSensitive(articleJSON, "description");
    if (!description) {
        goto end;
    }

    
    if(!cJSON_IsString(description))
    {
    goto end; //String
    }

    // article->body
    cJSON *body = cJSON_GetObjectItemCaseSensitive(articleJSON, "body");
    if (!body) {
        goto end;
    }

    
    if(!cJSON_IsString(body))
    {
    goto end; //String
    }

    // article->tag_list
    cJSON *tag_list = cJSON_GetObjectItemCaseSensitive(articleJSON, "tagList");
    if (!tag_list) {
        goto end;
    }

    
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

    // article->created_at
    cJSON *created_at = cJSON_GetObjectItemCaseSensitive(articleJSON, "createdAt");
    if (!created_at) {
        goto end;
    }

    
    if(!cJSON_IsString(created_at))
    {
    goto end; //DateTime
    }

    // article->updated_at
    cJSON *updated_at = cJSON_GetObjectItemCaseSensitive(articleJSON, "updatedAt");
    if (!updated_at) {
        goto end;
    }

    
    if(!cJSON_IsString(updated_at))
    {
    goto end; //DateTime
    }

    // article->favorited
    cJSON *favorited = cJSON_GetObjectItemCaseSensitive(articleJSON, "favorited");
    if (!favorited) {
        goto end;
    }

    
    if(!cJSON_IsBool(favorited))
    {
    goto end; //Bool
    }

    // article->favorites_count
    cJSON *favorites_count = cJSON_GetObjectItemCaseSensitive(articleJSON, "favoritesCount");
    if (!favorites_count) {
        goto end;
    }

    
    if(!cJSON_IsNumber(favorites_count))
    {
    goto end; //Numeric
    }

    // article->author
    cJSON *author = cJSON_GetObjectItemCaseSensitive(articleJSON, "author");
    if (!author) {
        goto end;
    }

    
    author_local_nonprim = profile_parseFromJSON(author); //nonprimitive


    article_local_var = article_create (
        strdup(slug->valuestring),
        strdup(title->valuestring),
        strdup(description->valuestring),
        strdup(body->valuestring),
        tag_listList,
        strdup(created_at->valuestring),
        strdup(updated_at->valuestring),
        favorited->valueint,
        favorites_count->valuedouble,
        author_local_nonprim
        );

    return article_local_var;
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
    if (author_local_nonprim) {
        profile_free(author_local_nonprim);
        author_local_nonprim = NULL;
    }
    return NULL;

}
