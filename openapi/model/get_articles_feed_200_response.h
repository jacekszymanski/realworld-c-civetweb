/*
 * get_articles_feed_200_response.h
 *
 * 
 */

#ifndef _get_articles_feed_200_response_H_
#define _get_articles_feed_200_response_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct get_articles_feed_200_response_t get_articles_feed_200_response_t;

#include "article.h"



typedef struct get_articles_feed_200_response_t {
    list_t *articles; //nonprimitive container
    int articles_count; //numeric

} get_articles_feed_200_response_t;

get_articles_feed_200_response_t *get_articles_feed_200_response_create(
    list_t *articles,
    int articles_count
);

void get_articles_feed_200_response_free(get_articles_feed_200_response_t *get_articles_feed_200_response);

get_articles_feed_200_response_t *get_articles_feed_200_response_parseFromJSON(cJSON *get_articles_feed_200_responseJSON);

cJSON *get_articles_feed_200_response_convertToJSON(get_articles_feed_200_response_t *get_articles_feed_200_response);

#endif /* _get_articles_feed_200_response_H_ */

