#ifndef __MACROS_H__
#define __MACROS_H__

#include "log.h"

#define SFREE(ptr) do { if (ptr) { free(ptr); ptr = NULL; } } while (0)
#define SFFREE(freefunc, ptr) do { if (ptr) { freefunc(ptr); ptr = NULL; } } while (0)

#define SET_FAIL(ctx, what) do { \
    WLOGS("failed to " what); \
    if(!(ctx)->respsealed) reqctx_set_error(ctx, 500, "failed to " what); \
    } while (0)

#define SET_FAIL_CODE(ctx, code, what) do { \
    WLOGS("failed to " what); \
    if(!(ctx)->respsealed) reqctx_set_error(ctx, code, "failed to " what); \
    } while (0)

#define NULL_FAIL(ctx, ptr, what) do { \
    if (!(ptr)) { \
      SET_FAIL(ctx, what); \
      } \
    } while (0)

#define NULL_FAIL_FAST(ctx, ptr, ret, what) do { \
    if (!(ptr)) { \
      SET_FAIL(ctx, what); \
      return ret; \
      } \
    } while (0)

#define RESP_SEALED_FAIL_FAST(ctx, ret) do { \
    if ((ctx)->respsealed) { \
      return ret; \
      } \
    } while (0)

#endif // __MACROS_H__
