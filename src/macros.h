#ifndef __MACROS_H__
#define __MACROS_H__

#include "log.h"

#define SFREE(ptr) do { if (ptr) { free(ptr); ptr = NULL; } } while (0)
#define SFFREE(freefunc, ptr) do { if (ptr) { freefunc(ptr); ptr = NULL; } } while (0)

#define NULL_FAIL_FAST(ctx, ptr, ret, what) do { \
    if (!ptr) { \
      WLOGS("failed to " what); \
      if(!(ctx)->respsent) mg_send_http_error((ctx)->conn, 500, "failed to " what); \
      (ctx)->respsent = 1; \
      return ret; \
      } \
    } while (0)

#define RESP_SENT_FAIL_FAST(ctx, ret) do { \
    if ((ctx)->respsent) { \
      return ret; \
      } \
    } while (0)

#endif // __MACROS_H__
