#include <stdlib.h>
#include <stdio.h>
#include "../include/apiClient.h"
#include "../include/list.h"
#include "../external/cJSON.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
#include "../model/generic_error_model.h"
#include "../model/get_profile_by_username_200_response.h"


// Follow a user
//
// Follow a user by username
//
get_profile_by_username_200_response_t*
ProfileAPI_followUserByUsername(apiClient_t *apiClient, char * username );


// Get a profile
//
// Get a profile of a user of the system. Auth is optional
//
get_profile_by_username_200_response_t*
ProfileAPI_getProfileByUsername(apiClient_t *apiClient, char * username );


// Unfollow a user
//
// Unfollow a user by username
//
get_profile_by_username_200_response_t*
ProfileAPI_unfollowUserByUsername(apiClient_t *apiClient, char * username );


