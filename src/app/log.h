#ifndef __LOG_H__
#define __LOG_H__

#include <stdio.h>

/*
 * loglevels:
 * -1 - no logging (don't use this)
 * 0 - only errors (ELOG)
 * 1 - warnings (WLOG)
 * 2 - infos (ILOG)
 * 3 - debug (DLOG)
 * 4 - trace (TLOG)
 * 5 - vomit (VLOG)
 *
 * default: 5 while I'm writing, then 2
 */

#ifndef LOGLEVEL
#define LOGLEVEL 5
#endif

#if LOGLEVEL >= 5
#define __LOG_VOMIT__ 1
#else
#define __LOG_VOMIT__ 0
#endif

#if LOGLEVEL >= 4
#define __LOG_TRACE__ 1
#else
#define __LOG_TRACE__ 0
#endif

#if LOGLEVEL >= 3
#define __LOG_DEBUG__ 1
#else
#define __LOG_DEBUG__ 0
#endif

#if LOGLEVEL >= 2
#define __LOG_INFO__ 1
#else
#define __LOG_INFO__ 0
#endif

#if LOGLEVEL >= 1
#define __LOG_WARN__ 1
#else
#define __LOG_WARN__ 0
#endif

#if LOGLEVEL >= 0
#define __LOG_ERROR__ 1
#else
#warning "LOGLEVEL is set to 0 or lower, no errors will be logged"
#define __LOG_ERROR__ 0
#endif

#define ELOG(fmt, ...)                              \
  do                                                \
  {                                                 \
    if (__LOG_ERROR__)                              \
      fprintf(stderr, "%s:%d:%s(): " fmt, __FILE__, \
              __LINE__, __func__, __VA_ARGS__);     \
  } while (0)

#define WLOG(fmt, ...)                              \
  do                                                \
  {                                                 \
    if (__LOG_WARN__)                               \
      fprintf(stderr, "%s:%d:%s(): " fmt, __FILE__, \
              __LINE__, __func__, __VA_ARGS__);     \
  } while (0)

#define ILOG(fmt, ...)                              \
  do                                                \
  {                                                 \
    if (__LOG_INFO__)                               \
      fprintf(stderr, "%s:%d:%s(): " fmt, __FILE__, \
              __LINE__, __func__, __VA_ARGS__);     \
  } while (0)

#define DLOG(fmt, ...)                              \
  do                                                \
  {                                                 \
    if (__LOG_DEBUG__)                              \
      fprintf(stderr, "%s:%d:%s(): " fmt, __FILE__, \
              __LINE__, __func__, __VA_ARGS__);     \
  } while (0)

#define TLOG(fmt, ...)                              \
  do                                                \
  {                                                 \
    if (__LOG_TRACE__)                              \
      fprintf(stderr, "%s:%d:%s(): " fmt, __FILE__, \
              __LINE__, __func__, __VA_ARGS__);     \
  } while (0)

#define VLOG(fmt, ...)                              \
  do                                                \
  {                                                 \
    if (__LOG_VOMIT__)                              \
      fprintf(stderr, "%s:%d:%s(): " fmt, __FILE__, \
              __LINE__, __func__, __VA_ARGS__);     \
  } while (0)

#define ELOGS(str) ELOG("%s\n", str)
#define WLOGS(str) WLOG("%s\n", str)
#define ILOGS(str) ILOG("%s\n", str)
#define DLOGS(str) DLOG("%s\n", str)
#define TLOGS(str) TLOG("%s\n", str)
#define VLOGS(str) VLOG("%s\n", str)

#endif // __LOG_H__
