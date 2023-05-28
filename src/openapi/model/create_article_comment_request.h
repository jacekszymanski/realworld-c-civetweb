/*
 * create_article_comment_request.h
 *
 * 
 */

#ifndef _create_article_comment_request_H_
#define _create_article_comment_request_H_

#include <string.h>
#include <cjson/cJSON.h>
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct create_article_comment_request_t create_article_comment_request_t;

#include "new_comment.h"



typedef struct create_article_comment_request_t {
    struct new_comment_t *comment; //model

} create_article_comment_request_t;

create_article_comment_request_t *create_article_comment_request_create(
    new_comment_t *comment
);

void create_article_comment_request_free(create_article_comment_request_t *create_article_comment_request);

create_article_comment_request_t *create_article_comment_request_parseFromJSON(cJSON *create_article_comment_requestJSON);

cJSON *create_article_comment_request_convertToJSON(create_article_comment_request_t *create_article_comment_request);

#endif /* _create_article_comment_request_H_ */

