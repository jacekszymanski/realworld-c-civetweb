#include <stdlib.h>
#include <stdio.h>
#include "../include/apiClient.h"
#include "../include/list.h"
#include "../external/cJSON.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
#include "../model/create_article_comment_200_response.h"
#include "../model/create_article_comment_request.h"
#include "../model/generic_error_model.h"
#include "../model/get_article_comments_200_response.h"


// Create a comment for an article
//
// Create a comment for an article. Auth is required
//
create_article_comment_200_response_t*
CommentsAPI_createArticleComment(apiClient_t *apiClient, char * slug , create_article_comment_request_t * comment );


// Delete a comment for an article
//
// Delete a comment for an article. Auth is required
//
void
CommentsAPI_deleteArticleComment(apiClient_t *apiClient, char * slug , int id );


// Get comments for an article
//
// Get the comments for an article. Auth is optional
//
get_article_comments_200_response_t*
CommentsAPI_getArticleComments(apiClient_t *apiClient, char * slug );


