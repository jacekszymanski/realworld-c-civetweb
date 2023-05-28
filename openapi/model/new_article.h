/*
 * new_article.h
 *
 * 
 */

#ifndef _new_article_H_
#define _new_article_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct new_article_t new_article_t;




typedef struct new_article_t {
    char *title; // string
    char *description; // string
    char *body; // string
    list_t *tag_list; //primitive container

} new_article_t;

new_article_t *new_article_create(
    char *title,
    char *description,
    char *body,
    list_t *tag_list
);

void new_article_free(new_article_t *new_article);

new_article_t *new_article_parseFromJSON(cJSON *new_articleJSON);

cJSON *new_article_convertToJSON(new_article_t *new_article);

#endif /* _new_article_H_ */

