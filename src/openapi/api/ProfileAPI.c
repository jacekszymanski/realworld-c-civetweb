#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "ProfileAPI.h"

#include <app/appctx.h>
#include <app/log.h>
#include <app/macros.h>
#include <app/util.h>
#include <db/db.h>

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
ProfileAPI_followUserByUsername(struct reqctx *ctx, const char *username) {
  return NULL;
}

// get profile
get_profile_by_username_200_response_t*
ProfileAPI_getProfileByUsername(struct reqctx *ctx, const char *username) {
  NULL_FAIL_FAST(ctx, username, NULL, "get username");

  profile_t *profile =
      db_get_profile_by_username(ctx->db, username, (ctx->curuser ? ctx->curuser->username : NULL));

  NULL_FAIL_FAST(ctx, profile, NULL, "get profile");

  get_profile_by_username_200_response_t *response = get_profile_by_username_200_response_create(profile);
  if (response == NULL)
  {
      WLOGS("Failed to create get profile response");
      profile_free(profile);
      return NULL;
  }

  TLOGS("created get profile response");

  return response;
}

// Unfollow a user
//
// Unfollow a user by username
//
get_profile_by_username_200_response_t*
ProfileAPI_unfollowUserByUsername(struct reqctx *ctx, const char *username) {
  return NULL;
}

