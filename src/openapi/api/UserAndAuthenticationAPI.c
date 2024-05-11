#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "UserAndAuthenticationAPI.h"

#include "../model/login_200_response.h"
#include "../model/login_request.h"

#include "../model/new_user.h"
#include "../model/user.h"
#include "../../db.h"
#include "../../log.h"
#include "../../macros.h"
#include "../../appctx.h"

#define MAX_NUMBER_LENGTH 16
#define MAX_BUFFER_LENGTH 4096
#define intToStr(dst, src) \
    do {\
    char dst[256];\
    snprintf(dst, 256, "%ld", (long int)(src));\
}while(0)


// Register a new user
//
login_200_response_t* UserAndAuthenticationAPI_createUser(struct reqctx *ctx, create_user_request_t * body )
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

    REQCTX_SET_ERROR(ctx, 201, "User created");
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
UserAndAuthenticationAPI_login(struct reqctx *ctx, login_request_t * body ) {
  if (body == NULL) return NULL;

  login_200_response_t *response = NULL;

  const char *email = body->user->email;
  const char *password = body->user->password;

  if (!(email && *email && password && *password)) {
    ILOGS("Bad email or password");
    REQCTX_SET_ERROR(ctx, 401, "Bad email or password");
    return NULL;
  }

  user_t *user = db_find_user_by_email(email);

  if (user == NULL) {
    WLOGS("Error finding user by email");
    return NULL;
  }

  if (user->email == NULL || strcmp(user->token, password) != 0) {
    DLOGS("Bad email or password");
    REQCTX_SET_ERROR(ctx, 401, "Bad email or password");
  }
  else {
    response = login_200_response_create(user);
    if (response == NULL) {
      WLOGS("Failed to create login response");
      REQCTX_SET_ERROR(ctx, 500, "Failed to create login response");
    }
    else {
      // FIXME: when I have a real token...
      char *token = malloc(MAX_BUFFER_LENGTH);
      if (token == NULL) {
        WLOGS("Failed to create token");
        REQCTX_SET_ERROR(ctx, 500, "Failed to create token");
      }
      else {
        snprintf(token, MAX_BUFFER_LENGTH, "%s:%s", "Token ", user->email);
        user->token = token;
        TLOGS("created login response");

        REQCTX_SET_ERROR(ctx, 200, "User logged in");
      }
    }
  }

  if (ctx->respcode != 200) {
    DLOGS("failed to login user");
    user_free(user);
    if (response) response->user = NULL;
    login_200_response_free(response);
    response = NULL;

    VLOGS("freed user and response");
  }

  return response;
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

