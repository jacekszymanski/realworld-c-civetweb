#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "ArticlesAPI.h"

#define MAX_NUMBER_LENGTH 16
#define MAX_BUFFER_LENGTH 4096
#define intToStr(dst, src) \
    do {\
    char dst[256];\
    snprintf(dst, 256, "%ld", (long int)(src));\
}while(0)


// Create an article
//
// Create an article. Auth is required
//
create_article_201_response_t*
ArticlesAPI_createArticle(apiClient_t *apiClient, create_article_request_t * article )
{
    list_t    *localVarQueryParameters = NULL;
    list_t    *localVarHeaderParameters = NULL;
    list_t    *localVarFormParameters = NULL;
    list_t *localVarHeaderType = list_createList();
    list_t *localVarContentType = list_createList();
    char      *localVarBodyParameters = NULL;

    // create the path
    long sizeOfPath = strlen("/articles")+1;
    char *localVarPath = malloc(sizeOfPath);
    snprintf(localVarPath, sizeOfPath, "/articles");




    // Body Param
    cJSON *localVarSingleItemJSON_article = NULL;
    if (article != NULL)
    {
        //string
        localVarSingleItemJSON_article = create_article_request_convertToJSON(article);
        localVarBodyParameters = cJSON_Print(localVarSingleItemJSON_article);
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
    //if (apiClient->response_code == 201) {
    //    printf("%s\n","Single article");
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
    cJSON *ArticlesAPIlocalVarJSON = cJSON_Parse(apiClient->dataReceived);
    create_article_201_response_t *elementToReturn = create_article_201_response_parseFromJSON(ArticlesAPIlocalVarJSON);
    cJSON_Delete(ArticlesAPIlocalVarJSON);
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
    if (localVarSingleItemJSON_article) {
        cJSON_Delete(localVarSingleItemJSON_article);
        localVarSingleItemJSON_article = NULL;
    }
    free(localVarBodyParameters);
    return elementToReturn;
end:
    free(localVarPath);
    return NULL;

}

// Delete an article
//
// Delete an article. Auth is required
//
void
ArticlesAPI_deleteArticle(apiClient_t *apiClient, char * slug )
{
    list_t    *localVarQueryParameters = NULL;
    list_t    *localVarHeaderParameters = NULL;
    list_t    *localVarFormParameters = NULL;
    list_t *localVarHeaderType = list_createList();
    list_t *localVarContentType = NULL;
    char      *localVarBodyParameters = NULL;

    // create the path
    long sizeOfPath = strlen("/articles/{slug}")+1;
    char *localVarPath = malloc(sizeOfPath);
    snprintf(localVarPath, sizeOfPath, "/articles/{slug}");


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

}

// Get an article
//
// Get an article. Auth not required
//
create_article_201_response_t*
ArticlesAPI_getArticle(apiClient_t *apiClient, char * slug )
{
    list_t    *localVarQueryParameters = NULL;
    list_t    *localVarHeaderParameters = NULL;
    list_t    *localVarFormParameters = NULL;
    list_t *localVarHeaderType = list_createList();
    list_t *localVarContentType = NULL;
    char      *localVarBodyParameters = NULL;

    // create the path
    long sizeOfPath = strlen("/articles/{slug}")+1;
    char *localVarPath = malloc(sizeOfPath);
    snprintf(localVarPath, sizeOfPath, "/articles/{slug}");


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
    //    printf("%s\n","Single article");
    //}
    // uncomment below to debug the error response
    //if (apiClient->response_code == 422) {
    //    printf("%s\n","Unexpected error");
    //}
    //nonprimitive not container
    cJSON *ArticlesAPIlocalVarJSON = cJSON_Parse(apiClient->dataReceived);
    create_article_201_response_t *elementToReturn = create_article_201_response_parseFromJSON(ArticlesAPIlocalVarJSON);
    cJSON_Delete(ArticlesAPIlocalVarJSON);
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

// Get recent articles globally
//
// Get most recent articles globally. Use query parameters to filter results. Auth is optional
//
get_articles_feed_200_response_t*
ArticlesAPI_getArticles(apiClient_t *apiClient, char * tag , char * author , char * favorited , int offset , int limit )
{
    list_t    *localVarQueryParameters = list_createList();
    list_t    *localVarHeaderParameters = NULL;
    list_t    *localVarFormParameters = NULL;
    list_t *localVarHeaderType = list_createList();
    list_t *localVarContentType = NULL;
    char      *localVarBodyParameters = NULL;

    // create the path
    long sizeOfPath = strlen("/articles")+1;
    char *localVarPath = malloc(sizeOfPath);
    snprintf(localVarPath, sizeOfPath, "/articles");




    // query parameters
    char *keyQuery_tag = NULL;
    char * valueQuery_tag = NULL;
    keyValuePair_t *keyPairQuery_tag = 0;
    if (tag)
    {
        keyQuery_tag = strdup("tag");
        valueQuery_tag = strdup((tag));
        keyPairQuery_tag = keyValuePair_create(keyQuery_tag, valueQuery_tag);
        list_addElement(localVarQueryParameters,keyPairQuery_tag);
    }

    // query parameters
    char *keyQuery_author = NULL;
    char * valueQuery_author = NULL;
    keyValuePair_t *keyPairQuery_author = 0;
    if (author)
    {
        keyQuery_author = strdup("author");
        valueQuery_author = strdup((author));
        keyPairQuery_author = keyValuePair_create(keyQuery_author, valueQuery_author);
        list_addElement(localVarQueryParameters,keyPairQuery_author);
    }

    // query parameters
    char *keyQuery_favorited = NULL;
    char * valueQuery_favorited = NULL;
    keyValuePair_t *keyPairQuery_favorited = 0;
    if (favorited)
    {
        keyQuery_favorited = strdup("favorited");
        valueQuery_favorited = strdup((favorited));
        keyPairQuery_favorited = keyValuePair_create(keyQuery_favorited, valueQuery_favorited);
        list_addElement(localVarQueryParameters,keyPairQuery_favorited);
    }

    // query parameters
    char *keyQuery_offset = NULL;
    char * valueQuery_offset = NULL;
    keyValuePair_t *keyPairQuery_offset = 0;
    if (offset)
    {
        keyQuery_offset = strdup("offset");
        valueQuery_offset = calloc(1,MAX_NUMBER_LENGTH);
        snprintf(valueQuery_offset, MAX_NUMBER_LENGTH, "%d", offset);
        keyPairQuery_offset = keyValuePair_create(keyQuery_offset, valueQuery_offset);
        list_addElement(localVarQueryParameters,keyPairQuery_offset);
    }

    // query parameters
    char *keyQuery_limit = NULL;
    char * valueQuery_limit = NULL;
    keyValuePair_t *keyPairQuery_limit = 0;
    if (limit)
    {
        keyQuery_limit = strdup("limit");
        valueQuery_limit = calloc(1,MAX_NUMBER_LENGTH);
        snprintf(valueQuery_limit, MAX_NUMBER_LENGTH, "%d", limit);
        keyPairQuery_limit = keyValuePair_create(keyQuery_limit, valueQuery_limit);
        list_addElement(localVarQueryParameters,keyPairQuery_limit);
    }
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
    //    printf("%s\n","Multiple articles");
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
    cJSON *ArticlesAPIlocalVarJSON = cJSON_Parse(apiClient->dataReceived);
    get_articles_feed_200_response_t *elementToReturn = get_articles_feed_200_response_parseFromJSON(ArticlesAPIlocalVarJSON);
    cJSON_Delete(ArticlesAPIlocalVarJSON);
    if(elementToReturn == NULL) {
        // return 0;
    }

    //return type
    if (apiClient->dataReceived) {
        free(apiClient->dataReceived);
        apiClient->dataReceived = NULL;
        apiClient->dataReceivedLen = 0;
    }
    list_freeList(localVarQueryParameters);
    
    
    list_freeList(localVarHeaderType);
    
    free(localVarPath);
    if(keyQuery_tag){
        free(keyQuery_tag);
        keyQuery_tag = NULL;
    }
    if(valueQuery_tag){
        free(valueQuery_tag);
        valueQuery_tag = NULL;
    }
    if(keyPairQuery_tag){
        keyValuePair_free(keyPairQuery_tag);
        keyPairQuery_tag = NULL;
    }
    if(keyQuery_author){
        free(keyQuery_author);
        keyQuery_author = NULL;
    }
    if(valueQuery_author){
        free(valueQuery_author);
        valueQuery_author = NULL;
    }
    if(keyPairQuery_author){
        keyValuePair_free(keyPairQuery_author);
        keyPairQuery_author = NULL;
    }
    if(keyQuery_favorited){
        free(keyQuery_favorited);
        keyQuery_favorited = NULL;
    }
    if(valueQuery_favorited){
        free(valueQuery_favorited);
        valueQuery_favorited = NULL;
    }
    if(keyPairQuery_favorited){
        keyValuePair_free(keyPairQuery_favorited);
        keyPairQuery_favorited = NULL;
    }
    if(keyQuery_offset){
        free(keyQuery_offset);
        keyQuery_offset = NULL;
    }
    if(valueQuery_offset){
        free(valueQuery_offset);
        valueQuery_offset = NULL;
    }
    if(keyPairQuery_offset){
        keyValuePair_free(keyPairQuery_offset);
        keyPairQuery_offset = NULL;
    }
    if(keyQuery_limit){
        free(keyQuery_limit);
        keyQuery_limit = NULL;
    }
    if(valueQuery_limit){
        free(valueQuery_limit);
        valueQuery_limit = NULL;
    }
    if(keyPairQuery_limit){
        keyValuePair_free(keyPairQuery_limit);
        keyPairQuery_limit = NULL;
    }
    return elementToReturn;
end:
    free(localVarPath);
    return NULL;

}

// Get recent articles from users you follow
//
// Get most recent articles from users you follow. Use query parameters to limit. Auth is required
//
get_articles_feed_200_response_t*
ArticlesAPI_getArticlesFeed(apiClient_t *apiClient, int offset , int limit )
{
    list_t    *localVarQueryParameters = list_createList();
    list_t    *localVarHeaderParameters = NULL;
    list_t    *localVarFormParameters = NULL;
    list_t *localVarHeaderType = list_createList();
    list_t *localVarContentType = NULL;
    char      *localVarBodyParameters = NULL;

    // create the path
    long sizeOfPath = strlen("/articles/feed")+1;
    char *localVarPath = malloc(sizeOfPath);
    snprintf(localVarPath, sizeOfPath, "/articles/feed");




    // query parameters
    char *keyQuery_offset = NULL;
    char * valueQuery_offset = NULL;
    keyValuePair_t *keyPairQuery_offset = 0;
    if (offset)
    {
        keyQuery_offset = strdup("offset");
        valueQuery_offset = calloc(1,MAX_NUMBER_LENGTH);
        snprintf(valueQuery_offset, MAX_NUMBER_LENGTH, "%d", offset);
        keyPairQuery_offset = keyValuePair_create(keyQuery_offset, valueQuery_offset);
        list_addElement(localVarQueryParameters,keyPairQuery_offset);
    }

    // query parameters
    char *keyQuery_limit = NULL;
    char * valueQuery_limit = NULL;
    keyValuePair_t *keyPairQuery_limit = 0;
    if (limit)
    {
        keyQuery_limit = strdup("limit");
        valueQuery_limit = calloc(1,MAX_NUMBER_LENGTH);
        snprintf(valueQuery_limit, MAX_NUMBER_LENGTH, "%d", limit);
        keyPairQuery_limit = keyValuePair_create(keyQuery_limit, valueQuery_limit);
        list_addElement(localVarQueryParameters,keyPairQuery_limit);
    }
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
    //    printf("%s\n","Multiple articles");
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
    cJSON *ArticlesAPIlocalVarJSON = cJSON_Parse(apiClient->dataReceived);
    get_articles_feed_200_response_t *elementToReturn = get_articles_feed_200_response_parseFromJSON(ArticlesAPIlocalVarJSON);
    cJSON_Delete(ArticlesAPIlocalVarJSON);
    if(elementToReturn == NULL) {
        // return 0;
    }

    //return type
    if (apiClient->dataReceived) {
        free(apiClient->dataReceived);
        apiClient->dataReceived = NULL;
        apiClient->dataReceivedLen = 0;
    }
    list_freeList(localVarQueryParameters);
    
    
    list_freeList(localVarHeaderType);
    
    free(localVarPath);
    if(keyQuery_offset){
        free(keyQuery_offset);
        keyQuery_offset = NULL;
    }
    if(valueQuery_offset){
        free(valueQuery_offset);
        valueQuery_offset = NULL;
    }
    if(keyPairQuery_offset){
        keyValuePair_free(keyPairQuery_offset);
        keyPairQuery_offset = NULL;
    }
    if(keyQuery_limit){
        free(keyQuery_limit);
        keyQuery_limit = NULL;
    }
    if(valueQuery_limit){
        free(valueQuery_limit);
        valueQuery_limit = NULL;
    }
    if(keyPairQuery_limit){
        keyValuePair_free(keyPairQuery_limit);
        keyPairQuery_limit = NULL;
    }
    return elementToReturn;
end:
    free(localVarPath);
    return NULL;

}

// Update an article
//
// Update an article. Auth is required
//
create_article_201_response_t*
ArticlesAPI_updateArticle(apiClient_t *apiClient, char * slug , update_article_request_t * article )
{
    list_t    *localVarQueryParameters = NULL;
    list_t    *localVarHeaderParameters = NULL;
    list_t    *localVarFormParameters = NULL;
    list_t *localVarHeaderType = list_createList();
    list_t *localVarContentType = list_createList();
    char      *localVarBodyParameters = NULL;

    // create the path
    long sizeOfPath = strlen("/articles/{slug}")+1;
    char *localVarPath = malloc(sizeOfPath);
    snprintf(localVarPath, sizeOfPath, "/articles/{slug}");


    // Path Params
    long sizeOfPathParams_slug = strlen(slug)+3 + strlen("{ slug }");
    if(slug == NULL) {
        goto end;
    }
    char* localVarToReplace_slug = malloc(sizeOfPathParams_slug);
    sprintf(localVarToReplace_slug, "{%s}", "slug");

    localVarPath = strReplace(localVarPath, localVarToReplace_slug, slug);



    // Body Param
    cJSON *localVarSingleItemJSON_article = NULL;
    if (article != NULL)
    {
        //string
        localVarSingleItemJSON_article = update_article_request_convertToJSON(article);
        localVarBodyParameters = cJSON_Print(localVarSingleItemJSON_article);
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
                    "PUT");

    // uncomment below to debug the error response
    //if (apiClient->response_code == 200) {
    //    printf("%s\n","Single article");
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
    cJSON *ArticlesAPIlocalVarJSON = cJSON_Parse(apiClient->dataReceived);
    create_article_201_response_t *elementToReturn = create_article_201_response_parseFromJSON(ArticlesAPIlocalVarJSON);
    cJSON_Delete(ArticlesAPIlocalVarJSON);
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
    if (localVarSingleItemJSON_article) {
        cJSON_Delete(localVarSingleItemJSON_article);
        localVarSingleItemJSON_article = NULL;
    }
    free(localVarBodyParameters);
    return elementToReturn;
end:
    free(localVarPath);
    return NULL;

}

