#ifndef __MACROS_H__
#define __MACROS_H__

#include "log.h"

#define SFREE(ptr) do { if (ptr) { free(ptr); ptr = NULL; } } while (0)
#define SFFREE(freefunc, ptr) do { if (ptr) { freefunc(ptr); ptr = NULL; } } while (0)

#define NULL_FAIL_FAST(conn, ptr, ret, what) do { \
    if (!ptr) { \
      WLOGS("failed to " what); \
      mg_send_http_error(conn, 500, "failed to " what); \
      return ret; \
      } \
    } while (0)

#endif // __MACROS_H__
