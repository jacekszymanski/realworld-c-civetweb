#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "ProfileAPI.h"

#include "../..//appctx.h"

#define MAX_NUMBER_LENGTH 16
#define MAX_BUFFER_LENGTH 4096
#define intToStr(dst, src) \
    do {\
    char dst[256];\
    snprintf(dst, 256, "%ld", (long int)(src));\
}while(0)


// Follow a user
//
// Follow a user by username
//
get_profile_by_username_200_response_t*
ProfileAPI_followUserByUsername(struct reqctx *ctx, char *username) {
  return NULL;
}

// get profile
get_profile_by_username_200_response_t*
ProfileAPI_getProfileByUsername(struct reqctx *ctx, char *username) {
  return NULL;
}

// Unfollow a user
//
// Unfollow a user by username
//
get_profile_by_username_200_response_t*
ProfileAPI_unfollowUserByUsername(struct reqctx *ctx, char *username) {
  return NULL;
}

