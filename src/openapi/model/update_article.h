/*
 * update_article.h
 *
 * 
 */

#ifndef _update_article_H_
#define _update_article_H_

#include <string.h>
#include <cjson/cJSON.h>
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct update_article_t update_article_t;




typedef struct update_article_t {
    char *title; // string
    char *description; // string
    char *body; // string

} update_article_t;

update_article_t *update_article_create(
    char *title,
    char *description,
    char *body
);

void update_article_free(update_article_t *update_article);

update_article_t *update_article_parseFromJSON(cJSON *update_articleJSON);

cJSON *update_article_convertToJSON(update_article_t *update_article);

#endif /* _update_article_H_ */

