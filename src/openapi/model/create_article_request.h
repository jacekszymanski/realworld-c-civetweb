/*
 * create_article_request.h
 *
 * 
 */

#ifndef _create_article_request_H_
#define _create_article_request_H_

#include <string.h>
#include <cjson/cJSON.h>
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct create_article_request_t create_article_request_t;

#include "new_article.h"



typedef struct create_article_request_t {
    struct new_article_t *article; //model

} create_article_request_t;

create_article_request_t *create_article_request_create(
    new_article_t *article
);

void create_article_request_free(create_article_request_t *create_article_request);

create_article_request_t *create_article_request_parseFromJSON(cJSON *create_article_requestJSON);

cJSON *create_article_request_convertToJSON(create_article_request_t *create_article_request);

#endif /* _create_article_request_H_ */

