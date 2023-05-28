/*
 * new_comment.h
 *
 * 
 */

#ifndef _new_comment_H_
#define _new_comment_H_

#include <string.h>
#include <cjson/cJSON.h>
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct new_comment_t new_comment_t;




typedef struct new_comment_t {
    char *body; // string

} new_comment_t;

new_comment_t *new_comment_create(
    char *body
);

void new_comment_free(new_comment_t *new_comment);

new_comment_t *new_comment_parseFromJSON(cJSON *new_commentJSON);

cJSON *new_comment_convertToJSON(new_comment_t *new_comment);

#endif /* _new_comment_H_ */

