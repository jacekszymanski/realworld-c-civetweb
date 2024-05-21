#include <stdlib.h>
#include <stdio.h>
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
#include "../model/generic_error_model.h"
#include "../model/get_profile_by_username_200_response.h"

#include <app/appctx.h>

// Follow a user
//
// Follow a user by username
//
get_profile_by_username_200_response_t*
ProfileAPI_followUserByUsername(struct reqctx *ctx, const char * username );


// Get a profile
//
// Get a profile of a user of the system. Auth is optional
//
get_profile_by_username_200_response_t*
ProfileAPI_getProfileByUsername(struct reqctx *ctx, const char * username );


// Unfollow a user
//
// Unfollow a user by username
//
get_profile_by_username_200_response_t*
ProfileAPI_unfollowUserByUsername(struct reqctx *ctx, const char * username );


