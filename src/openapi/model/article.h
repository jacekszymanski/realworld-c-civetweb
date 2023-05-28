/*
 * article.h
 *
 * 
 */

#ifndef _article_H_
#define _article_H_

#include <string.h>
#include <cjson/cJSON.h>
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct article_t article_t;

#include "profile.h"



typedef struct article_t {
    char *slug; // string
    char *title; // string
    char *description; // string
    char *body; // string
    list_t *tag_list; //primitive container
    char *created_at; //date time
    char *updated_at; //date time
    int favorited; //boolean
    int favorites_count; //numeric
    struct profile_t *author; //model

} article_t;

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
);

void article_free(article_t *article);

article_t *article_parseFromJSON(cJSON *articleJSON);

cJSON *article_convertToJSON(article_t *article);

#endif /* _article_H_ */

