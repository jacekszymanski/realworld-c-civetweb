#include <stdlib.h>
#include <stdio.h>
#include "../include/apiClient.h"
#include "../include/list.h"
#include "../external/cJSON.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
#include "../model/generic_error_model.h"
#include "../model/get_tags_200_response.h"


// Get tags
//
// Get tags. Auth not required
//
get_tags_200_response_t*
TagsAPI_getTags(apiClient_t *apiClient);


