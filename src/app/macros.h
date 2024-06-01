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

#define CONCATENATE(arg1, arg2)   CONCATENATE1(arg1, arg2)
#define CONCATENATE1(arg1, arg2)  CONCATENATE2(arg1, arg2)
#define CONCATENATE2(arg1, arg2)  arg1##arg2

#define FOR_EACH_L_1(what, x, ...) what(x)
#define FOR_EACH_L_2(what, x, ...)\
  what(x),\
  FOR_EACH_L_1(what,  __VA_ARGS__)
#define FOR_EACH_L_3(what, x, ...)\
  what(x),\
  FOR_EACH_L_2(what, __VA_ARGS__)
#define FOR_EACH_L_4(what, x, ...)\
  what(x),\
  FOR_EACH_L_3(what,  __VA_ARGS__)
#define FOR_EACH_L_5(what, x, ...)\
  what(x),\
 FOR_EACH_L_4(what,  __VA_ARGS__)
#define FOR_EACH_L_6(what, x, ...)\
  what(x),\
  FOR_EACH_L_5(what,  __VA_ARGS__)
#define FOR_EACH_L_7(what, x, ...)\
  what(x),\
  FOR_EACH_L_6(what,  __VA_ARGS__)
#define FOR_EACH_L_8(what, x, ...)\
  what(x),\
  FOR_EACH_L_7(what,  __VA_ARGS__)

#define FOR_EACH_L_NARG(...) FOR_EACH_L_NARG_(__VA_ARGS__, FOR_EACH_L_RSEQ_N())
#define FOR_EACH_L_NARG_(...) FOR_EACH_L_ARG_N(__VA_ARGS__)
#define FOR_EACH_L_ARG_N(_1, _2, _3, _4, _5, _6, _7, _8, N, ...) N
#define FOR_EACH_L_RSEQ_N() 8, 7, 6, 5, 4, 3, 2, 1, 0

#define FOR_EACH_L_(N, what, x, ...) CONCATENATE(FOR_EACH_L_, N)(what, x, __VA_ARGS__)
#define FOR_EACH_L(what, x, ...) FOR_EACH_L_(FOR_EACH_L_NARG(x, __VA_ARGS__), what, x, __VA_ARGS__)


#endif // __MACROS_H__
