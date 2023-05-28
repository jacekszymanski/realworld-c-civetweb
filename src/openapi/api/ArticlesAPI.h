#include <stdlib.h>
#include <stdio.h>
#include "../include/apiClient.h"
#include "../include/list.h"
#include "../external/cJSON.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
#include "../model/create_article_201_response.h"
#include "../model/create_article_request.h"
#include "../model/generic_error_model.h"
#include "../model/get_articles_feed_200_response.h"
#include "../model/update_article_request.h"


// Create an article
//
// Create an article. Auth is required
//
create_article_201_response_t*
ArticlesAPI_createArticle(apiClient_t *apiClient, create_article_request_t * article );


// Delete an article
//
// Delete an article. Auth is required
//
void
ArticlesAPI_deleteArticle(apiClient_t *apiClient, char * slug );


// Get an article
//
// Get an article. Auth not required
//
create_article_201_response_t*
ArticlesAPI_getArticle(apiClient_t *apiClient, char * slug );


// Get recent articles globally
//
// Get most recent articles globally. Use query parameters to filter results. Auth is optional
//
get_articles_feed_200_response_t*
ArticlesAPI_getArticles(apiClient_t *apiClient, char * tag , char * author , char * favorited , int offset , int limit );


// Get recent articles from users you follow
//
// Get most recent articles from users you follow. Use query parameters to limit. Auth is required
//
get_articles_feed_200_response_t*
ArticlesAPI_getArticlesFeed(apiClient_t *apiClient, int offset , int limit );


// Update an article
//
// Update an article. Auth is required
//
create_article_201_response_t*
ArticlesAPI_updateArticle(apiClient_t *apiClient, char * slug , update_article_request_t * article );


