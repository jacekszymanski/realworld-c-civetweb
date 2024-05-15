#ifndef __USERANDAUTHENTICATIONAPI_H__
#define __USERANDAUTHENTICATIONAPI_H__

#include <stdlib.h>
#include <stdio.h>
#include "../model/create_user_request.h"
#include "../model/generic_error_model.h"
#include "../model/login_200_response.h"
#include "../model/login_request.h"
#include "../model/update_current_user_request.h"

#include "../../appctx.h"


// Register a new user
//
login_200_response_t*
UserAndAuthenticationAPI_createUser(struct reqctx *ctx, create_user_request_t * body );


// Get current user
//
// Gets the currently logged-in user
//
login_200_response_t*
UserAndAuthenticationAPI_getCurrentUser(struct reqctx *ctx);


// Existing user login
//
// Login for existing user
//
login_200_response_t*
UserAndAuthenticationAPI_login(struct reqctx *ctx, login_request_t * body );


// Update current user
//
// Updated user information for current user
//
login_200_response_t*
UserAndAuthenticationAPI_updateCurrentUser(update_current_user_request_t * body );


#endif // __USERANDAUTHENTICATIONAPI_H__
