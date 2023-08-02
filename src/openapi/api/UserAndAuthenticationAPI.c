#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "UserAndAuthenticationAPI.h"

#include "../model/new_user.h"
#include "../model/user.h"
#include "../../db.h"
#include "../../log.h"

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
  const new_user_t *new_user = body->user;
  if (new_user == NULL) return NULL;

  int res = db_create_user(new_user->username, new_user->email, new_user->password);

  if (res >= 0) {
    user_t *user = user_create(
      strdup(new_user->email),
      strdup(""),
      strdup(new_user->username),
      strdup(""),
      strdup("https://static.productionready.io/images/smiley-cyrus.jpg"));
    if (user == NULL) return NULL;

    login_200_response_t *response = login_200_response_create(user);
    if (response == NULL) {
      WLOGS("Failed to create login response");
      user_free(user);
      return NULL;
    }

    TLOGS("created login response");

    return response;
  } else {
    WLOGS("Failed to create user");
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
  (void)body;

  return NULL;
}

// Update current user
//
// Updated user information for current user
//
login_200_response_t*
UserAndAuthenticationAPI_updateCurrentUser(update_current_user_request_t * body ) {
  (void)body;

  return NULL;
}

