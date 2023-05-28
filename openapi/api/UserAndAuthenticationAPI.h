#include <stdlib.h>
#include <stdio.h>
#include "../include/apiClient.h"
#include "../include/list.h"
#include "../external/cJSON.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
#include "../model/create_user_request.h"
#include "../model/generic_error_model.h"
#include "../model/login_200_response.h"
#include "../model/login_request.h"
#include "../model/update_current_user_request.h"


// Register a new user
//
login_200_response_t*
UserAndAuthenticationAPI_createUser(apiClient_t *apiClient, create_user_request_t * body );


// Get current user
//
// Gets the currently logged-in user
//
login_200_response_t*
UserAndAuthenticationAPI_getCurrentUser(apiClient_t *apiClient);


// Existing user login
//
// Login for existing user
//
login_200_response_t*
UserAndAuthenticationAPI_login(apiClient_t *apiClient, login_request_t * body );


// Update current user
//
// Updated user information for current user
//
login_200_response_t*
UserAndAuthenticationAPI_updateCurrentUser(apiClient_t *apiClient, update_current_user_request_t * body );


