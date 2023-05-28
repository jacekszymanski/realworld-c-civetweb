/*
 * profile.h
 *
 * 
 */

#ifndef _profile_H_
#define _profile_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct profile_t profile_t;




typedef struct profile_t {
    char *username; // string
    char *bio; // string
    char *image; // string
    int following; //boolean

} profile_t;

profile_t *profile_create(
    char *username,
    char *bio,
    char *image,
    int following
);

void profile_free(profile_t *profile);

profile_t *profile_parseFromJSON(cJSON *profileJSON);

cJSON *profile_convertToJSON(profile_t *profile);

#endif /* _profile_H_ */

