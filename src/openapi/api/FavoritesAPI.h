#include <stdlib.h>
#include <stdio.h>
#include "../include/apiClient.h"
#include "../include/list.h"
#include "../external/cJSON.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
#include "../model/create_article_201_response.h"
#include "../model/generic_error_model.h"


// Favorite an article
//
// Favorite an article. Auth is required
//
create_article_201_response_t*
FavoritesAPI_createArticleFavorite(apiClient_t *apiClient, char * slug );


// Unfavorite an article
//
// Unfavorite an article. Auth is required
//
create_article_201_response_t*
FavoritesAPI_deleteArticleFavorite(apiClient_t *apiClient, char * slug );


