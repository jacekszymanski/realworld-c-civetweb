/*
 * comment.h
 *
 * 
 */

#ifndef _comment_H_
#define _comment_H_

#include <string.h>
#include <cjson/cJSON.h>
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct comment_t comment_t;

#include "profile.h"



typedef struct comment_t {
    int id; //numeric
    char *created_at; //date time
    char *updated_at; //date time
    char *body; // string
    struct profile_t *author; //model

} comment_t;

comment_t *comment_create(
    int id,
    char *created_at,
    char *updated_at,
    char *body,
    profile_t *author
);

void comment_free(comment_t *comment);

comment_t *comment_parseFromJSON(cJSON *commentJSON);

cJSON *comment_convertToJSON(comment_t *comment);

#endif /* _comment_H_ */

