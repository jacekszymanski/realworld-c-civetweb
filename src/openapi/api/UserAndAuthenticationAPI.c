#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "UserAndAuthenticationAPI.h"

#include "../openapi/model/new_user.h"
#include "../openapi/model/user.h"

#define MAX_NUMBER_LENGTH 16
#define MAX_BUFFER_LENGTH 4096
#define intToStr(dst, src) \
    do {\
    char dst[256];\
    snprintf(dst, 256, "%ld", (long int)(src));\
}while(0)


// Register a new user
//
login_200_response_t* UserAndAuthenticationAPI_createUser(create_user_request_t * body )
{
  if (body == NULL) return NULL;
  const new_user_t *new_user = body->new_user;
  if (new_user == NULL) return NULL;

  int res = db_create_user(new_user->username, new_user->email, new_user->password);

  if (res >= 0) {
    user_t *user = user_create(new_user->email, NULL, new_user->username, NULL, NULL);
    if (user == NULL) return NULL;

    login_200_response_t *response = login_200_response_create(user);
    if (response == NULL) {
      user_free(user);
      return NULL;
    }

    return response;
  } else {
    return NULL;
  }

}

// Get current user
//
// Gets the currently logged-in user
//
login_200_response_t* UserAndAuthenticationAPI_getCurrentUser()
{
  return NULL;
}

// Existing user login
//
// Login for existing user
//
login_200_response_t*
UserAndAuthenticationAPI_login(login_request_t * body ) {
  return NULL;
}

// Update current user
//
// Updated user information for current user
//
login_200_response_t*
UserAndAuthenticationAPI_updateCurrentUser(apiClient_t *apiClient, update_current_user_request_t * body ) {
  return NULL;
}

