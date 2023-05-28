/*
 * get_article_comments_200_response.h
 *
 * 
 */

#ifndef _get_article_comments_200_response_H_
#define _get_article_comments_200_response_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct get_article_comments_200_response_t get_article_comments_200_response_t;

#include "comment.h"



typedef struct get_article_comments_200_response_t {
    list_t *comments; //nonprimitive container

} get_article_comments_200_response_t;

get_article_comments_200_response_t *get_article_comments_200_response_create(
    list_t *comments
);

void get_article_comments_200_response_free(get_article_comments_200_response_t *get_article_comments_200_response);

get_article_comments_200_response_t *get_article_comments_200_response_parseFromJSON(cJSON *get_article_comments_200_responseJSON);

cJSON *get_article_comments_200_response_convertToJSON(get_article_comments_200_response_t *get_article_comments_200_response);

#endif /* _get_article_comments_200_response_H_ */

