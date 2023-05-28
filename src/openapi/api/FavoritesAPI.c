#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "FavoritesAPI.h"

#define MAX_NUMBER_LENGTH 16
#define MAX_BUFFER_LENGTH 4096
#define intToStr(dst, src) \
    do {\
    char dst[256];\
    snprintf(dst, 256, "%ld", (long int)(src));\
}while(0)


// Favorite an article
//
// Favorite an article. Auth is required
//
create_article_201_response_t*
FavoritesAPI_createArticleFavorite(apiClient_t *apiClient, char * slug )
{
    list_t    *localVarQueryParameters = NULL;
    list_t    *localVarHeaderParameters = NULL;
    list_t    *localVarFormParameters = NULL;
    list_t *localVarHeaderType = list_createList();
    list_t *localVarContentType = NULL;
    char      *localVarBodyParameters = NULL;

    // create the path
    long sizeOfPath = strlen("/articles/{slug}/favorite")+1;
    char *localVarPath = malloc(sizeOfPath);
    snprintf(localVarPath, sizeOfPath, "/articles/{slug}/favorite");


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
                    "POST");

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
    cJSON *FavoritesAPIlocalVarJSON = cJSON_Parse(apiClient->dataReceived);
    create_article_201_response_t *elementToReturn = create_article_201_response_parseFromJSON(FavoritesAPIlocalVarJSON);
    cJSON_Delete(FavoritesAPIlocalVarJSON);
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

// Unfavorite an article
//
// Unfavorite an article. Auth is required
//
create_article_201_response_t*
FavoritesAPI_deleteArticleFavorite(apiClient_t *apiClient, char * slug )
{
    list_t    *localVarQueryParameters = NULL;
    list_t    *localVarHeaderParameters = NULL;
    list_t    *localVarFormParameters = NULL;
    list_t *localVarHeaderType = list_createList();
    list_t *localVarContentType = NULL;
    char      *localVarBodyParameters = NULL;

    // create the path
    long sizeOfPath = strlen("/articles/{slug}/favorite")+1;
    char *localVarPath = malloc(sizeOfPath);
    snprintf(localVarPath, sizeOfPath, "/articles/{slug}/favorite");


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
    cJSON *FavoritesAPIlocalVarJSON = cJSON_Parse(apiClient->dataReceived);
    create_article_201_response_t *elementToReturn = create_article_201_response_parseFromJSON(FavoritesAPIlocalVarJSON);
    cJSON_Delete(FavoritesAPIlocalVarJSON);
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

