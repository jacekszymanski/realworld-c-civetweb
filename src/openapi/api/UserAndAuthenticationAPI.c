#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "UserAndAuthenticationAPI.h"

#include "../model/login_200_response.h"
#include "../model/login_request.h"

#include "../model/new_user.h"
#include "../model/user.h"

#include <app/db.h>
#include <app/log.h>
#include <app/macros.h>
#include <app/appctx.h>
#include <app/util.h>

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

  int res = db_create_user(ctx->db, new_user->username, new_user->email, new_user->password);

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
login_200_response_t* UserAndAuthenticationAPI_getCurrentUser(struct reqctx *ctx) {
  user_t *user = ctx->curuser;
  if (user) {
    VLOG("found current user %s\n", user->username);
    user_t *user_copy = user_create(
      safe_strdup(user->email),
      safe_strdup(""),
      safe_strdup(user->username),
      safe_strdup(user->bio),
      safe_strdup(user->image));

    if (!user_copy) {
      WLOGS("Failed to copy user");
      return NULL;
    }

    return login_200_response_create(user_copy);
  }

  WLOGS("Failed to create response");

  return NULL;

}

void bad_login(struct reqctx *ctx) {
  const char *msg = "Bad email or password";
  DLOGS(msg);
  reqctx_set_error(ctx, 401, msg);
}

// Existing user login
//
// Login for existing user
//
login_200_response_t*
UserAndAuthenticationAPI_login(struct reqctx *ctx, login_request_t * body ) {
  if (body == NULL) return NULL;

  int login_ok = 0;
  login_200_response_t *response = NULL;

  const char *email = body->user->email;
  const char *password = body->user->password;

  if (!(email && *email && password && *password)) {
    bad_login(ctx);
    return NULL;
  }

  user_t *user = db_find_user_by_email(ctx->db, email);
  NULL_FAIL_FAST(ctx, user, NULL, "find user by email");

  if (user->email == NULL || strcmp(user->token, password) != 0) {
    bad_login(ctx);
  }
  else {
    response = login_200_response_create(user);
    if (!response) {
      SET_FAIL(ctx, "create login response");
    }
    else {
      // FIXME: when I have a real token...
      char *token = malloc(MAX_BUFFER_LENGTH);
      if (!token) {
        SET_FAIL(ctx, "create token");
      }
      else {
        snprintf(token, MAX_BUFFER_LENGTH, "%s:%s", "Token ", user->email);
        user->token = token;
        TLOGS("created login response");

        login_ok = 1;
      }
    }
  }

  if (!login_ok) {
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

