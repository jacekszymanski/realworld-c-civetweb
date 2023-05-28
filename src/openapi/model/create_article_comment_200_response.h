/*
 * create_article_comment_200_response.h
 *
 * 
 */

#ifndef _create_article_comment_200_response_H_
#define _create_article_comment_200_response_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct create_article_comment_200_response_t create_article_comment_200_response_t;

#include "comment.h"



typedef struct create_article_comment_200_response_t {
    struct comment_t *comment; //model

} create_article_comment_200_response_t;

create_article_comment_200_response_t *create_article_comment_200_response_create(
    comment_t *comment
);

void create_article_comment_200_response_free(create_article_comment_200_response_t *create_article_comment_200_response);

create_article_comment_200_response_t *create_article_comment_200_response_parseFromJSON(cJSON *create_article_comment_200_responseJSON);

cJSON *create_article_comment_200_response_convertToJSON(create_article_comment_200_response_t *create_article_comment_200_response);

#endif /* _create_article_comment_200_response_H_ */

