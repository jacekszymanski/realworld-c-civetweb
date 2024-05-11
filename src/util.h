#ifndef __UTIL_H__
#define __UTIL_H__

const char* get_request_content(struct mg_connection* conn);
char* safe_strdup(const char* s);

#endif // __UTIL_H__
