/*
 * create_article_201_response.h
 *
 * 
 */

#ifndef _create_article_201_response_H_
#define _create_article_201_response_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct create_article_201_response_t create_article_201_response_t;

#include "article.h"



typedef struct create_article_201_response_t {
    struct article_t *article; //model

} create_article_201_response_t;

create_article_201_response_t *create_article_201_response_create(
    article_t *article
);

void create_article_201_response_free(create_article_201_response_t *create_article_201_response);

create_article_201_response_t *create_article_201_response_parseFromJSON(cJSON *create_article_201_responseJSON);

cJSON *create_article_201_response_convertToJSON(create_article_201_response_t *create_article_201_response);

#endif /* _create_article_201_response_H_ */

