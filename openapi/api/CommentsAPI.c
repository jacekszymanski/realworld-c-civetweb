#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "CommentsAPI.h"

#define MAX_NUMBER_LENGTH 16
#define MAX_BUFFER_LENGTH 4096
#define intToStr(dst, src) \
    do {\
    char dst[256];\
    snprintf(dst, 256, "%ld", (long int)(src));\
}while(0)


// Create a comment for an article
//
// Create a comment for an article. Auth is required
//
create_article_comment_200_response_t*
CommentsAPI_createArticleComment(apiClient_t *apiClient, char * slug , create_article_comment_request_t * comment )
{
    list_t    *localVarQueryParameters = NULL;
    list_t    *localVarHeaderParameters = NULL;
    list_t    *localVarFormParameters = NULL;
    list_t *localVarHeaderType = list_createList();
    list_t *localVarContentType = list_createList();
    char      *localVarBodyParameters = NULL;

    // create the path
    long sizeOfPath = strlen("/articles/{slug}/comments")+1;
    char *localVarPath = malloc(sizeOfPath);
    snprintf(localVarPath, sizeOfPath, "/articles/{slug}/comments");


    // Path Params
    long sizeOfPathParams_slug = strlen(slug)+3 + strlen("{ slug }");
    if(slug == NULL) {
        goto end;
    }
    char* localVarToReplace_slug = malloc(sizeOfPathParams_slug);
    sprintf(localVarToReplace_slug, "{%s}", "slug");

    localVarPath = strReplace(localVarPath, localVarToReplace_slug, slug);



    // Body Param
    cJSON *localVarSingleItemJSON_comment = NULL;
    if (comment != NULL)
    {
        //string
        localVarSingleItemJSON_comment = create_article_comment_request_convertToJSON(comment);
        localVarBodyParameters = cJSON_Print(localVarSingleItemJSON_comment);
    }
    list_addElement(localVarHeaderType,"application/json"); //produces
    list_addElement(localVarContentType,"application/json"); //consumes
    apiClient_invoke(apiClient,
                    localVarPath,
                    localVarQueryParameters,
                    localVarHeaderParameters,
                    localVarFormParameters,
                    localVarHeaderType,
                    localVarContentType,
                    localVarBodyParameters,
                    "POST");

    // uncomment below to debug the error response
    //if (apiClient->response_code == 200) {
    //    printf("%s\n","Single comment");
    //}
    // uncomment below to debug the error response
    //if (apiClient->response_code == 401) {
    //    printf("%s\n","Unauthorized");
    //}
    // uncomment below to debug the error response
    //if (apiClient->response_code == 422) {
    //    printf("%s\n","Unexpected error");
    //}
    //nonprimitive not container
    cJSON *CommentsAPIlocalVarJSON = cJSON_Parse(apiClient->dataReceived);
    create_article_comment_200_response_t *elementToReturn = create_article_comment_200_response_parseFromJSON(CommentsAPIlocalVarJSON);
    cJSON_Delete(CommentsAPIlocalVarJSON);
    if(elementToReturn == NULL) {
        // return 0;
    }

    //return type
    if (apiClient->dataReceived) {
        free(apiClient->dataReceived);
        apiClient->dataReceived = NULL;
        apiClient->dataReceivedLen = 0;
    }
    
    
    
    list_freeList(localVarHeaderType);
    list_freeList(localVarContentType);
    free(localVarPath);
    free(localVarToReplace_slug);
    if (localVarSingleItemJSON_comment) {
        cJSON_Delete(localVarSingleItemJSON_comment);
        localVarSingleItemJSON_comment = NULL;
    }
    free(localVarBodyParameters);
    return elementToReturn;
end:
    free(localVarPath);
    return NULL;

}

// Delete a comment for an article
//
// Delete a comment for an article. Auth is required
//
void
CommentsAPI_deleteArticleComment(apiClient_t *apiClient, char * slug , int id )
{
    list_t    *localVarQueryParameters = NULL;
    list_t    *localVarHeaderParameters = NULL;
    list_t    *localVarFormParameters = NULL;
    list_t *localVarHeaderType = list_createList();
    list_t *localVarContentType = NULL;
    char      *localVarBodyParameters = NULL;

    // create the path
    long sizeOfPath = strlen("/articles/{slug}/comments/{id}")+1;
    char *localVarPath = malloc(sizeOfPath);
    snprintf(localVarPath, sizeOfPath, "/articles/{slug}/comments/{id}");


    // Path Params
    long sizeOfPathParams_slug = strlen(slug)+3 +  + strlen("{ slug }");
    if(slug == NULL) {
        goto end;
    }
    char* localVarToReplace_slug = malloc(sizeOfPathParams_slug);
    sprintf(localVarToReplace_slug, "{%s}", "slug");

    localVarPath = strReplace(localVarPath, localVarToReplace_slug, slug);

    // Path Params
    long sizeOfPathParams_id = strlen(slug)+3 +  + strlen("{ id }");
    if(id == 0){
        goto end;
    }
    char* localVarToReplace_id = malloc(sizeOfPathParams_id);
    snprintf(localVarToReplace_id, sizeOfPathParams_id, "{%s}", "id");

    char localVarBuff_id[256];
    intToStr(localVarBuff_id, id);

    localVarPath = strReplace(localVarPath, localVarToReplace_id, localVarBuff_id);



    list_addElement(localVarHeaderType,"application/json"); //produces
    apiClient_invoke(apiClient,
                    localVarPath,
                    localVarQueryParameters,
                    localVarHeaderParameters,
                    localVarFormParameters,
                    localVarHeaderType,
                    localVarContentType,
                    localVarBodyParameters,
                    "DELETE");

    // uncomment below to debug the error response
    //if (apiClient->response_code == 200) {
    //    printf("%s\n","No content");
    //}
    // uncomment below to debug the error response
    //if (apiClient->response_code == 401) {
    //    printf("%s\n","Unauthorized");
    //}
    // uncomment below to debug the error response
    //if (apiClient->response_code == 422) {
    //    printf("%s\n","Unexpected error");
    //}
    //No return type
end:
    if (apiClient->dataReceived) {
        free(apiClient->dataReceived);
        apiClient->dataReceived = NULL;
        apiClient->dataReceivedLen = 0;
    }
    
    
    
    list_freeList(localVarHeaderType);
    
    free(localVarPath);
    free(localVarToReplace_slug);
    free(localVarToReplace_id);

}

// Get comments for an article
//
// Get the comments for an article. Auth is optional
//
get_article_comments_200_response_t*
CommentsAPI_getArticleComments(apiClient_t *apiClient, char * slug )
{
    list_t    *localVarQueryParameters = NULL;
    list_t    *localVarHeaderParameters = NULL;
    list_t    *localVarFormParameters = NULL;
    list_t *localVarHeaderType = list_createList();
    list_t *localVarContentType = NULL;
    char      *localVarBodyParameters = NULL;

    // create the path
    long sizeOfPath = strlen("/articles/{slug}/comments")+1;
    char *localVarPath = malloc(sizeOfPath);
    snprintf(localVarPath, sizeOfPath, "/articles/{slug}/comments");


    // Path Params
    long sizeOfPathParams_slug = strlen(slug)+3 + strlen("{ slug }");
    if(slug == NULL) {
        goto end;
    }
    char* localVarToReplace_slug = malloc(sizeOfPathParams_slug);
    sprintf(localVarToReplace_slug, "{%s}", "slug");

    localVarPath = strReplace(localVarPath, localVarToReplace_slug, slug);


    list_addElement(localVarHeaderType,"application/json"); //produces
    apiClient_invoke(apiClient,
                    localVarPath,
                    localVarQueryParameters,
                    localVarHeaderParameters,
                    localVarFormParameters,
                    localVarHeaderType,
                    localVarContentType,
                    localVarBodyParameters,
                    "GET");

    // uncomment below to debug the error response
    //if (apiClient->response_code == 200) {
    //    printf("%s\n","Multiple comments");
    //}
    // uncomment below to debug the error response
    //if (apiClient->response_code == 401) {
    //    printf("%s\n","Unauthorized");
    //}
    // uncomment below to debug the error response
    //if (apiClient->response_code == 422) {
    //    printf("%s\n","Unexpected error");
    //}
    //nonprimitive not container
    cJSON *CommentsAPIlocalVarJSON = cJSON_Parse(apiClient->dataReceived);
    get_article_comments_200_response_t *elementToReturn = get_article_comments_200_response_parseFromJSON(CommentsAPIlocalVarJSON);
    cJSON_Delete(CommentsAPIlocalVarJSON);
    if(elementToReturn == NULL) {
        // return 0;
    }

    //return type
    if (apiClient->dataReceived) {
        free(apiClient->dataReceived);
        apiClient->dataReceived = NULL;
        apiClient->dataReceivedLen = 0;
    }
    
    
    
    list_freeList(localVarHeaderType);
    
    free(localVarPath);
    free(localVarToReplace_slug);
    return elementToReturn;
end:
    free(localVarPath);
    return NULL;

}

