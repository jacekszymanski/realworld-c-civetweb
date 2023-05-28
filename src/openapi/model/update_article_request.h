/*
 * update_article_request.h
 *
 * 
 */

#ifndef _update_article_request_H_
#define _update_article_request_H_

#include <string.h>
#include <cjson/cJSON.h>
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct update_article_request_t update_article_request_t;

#include "update_article.h"



typedef struct update_article_request_t {
    struct update_article_t *article; //model

} update_article_request_t;

update_article_request_t *update_article_request_create(
    update_article_t *article
);

void update_article_request_free(update_article_request_t *update_article_request);

update_article_request_t *update_article_request_parseFromJSON(cJSON *update_article_requestJSON);

cJSON *update_article_request_convertToJSON(update_article_request_t *update_article_request);

#endif /* _update_article_request_H_ */

