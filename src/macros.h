#ifndef __MACROS_H__
#define __MACROS_H__

#define SFREE(ptr) do { if (ptr) { free(ptr); ptr = NULL; } } while (0)
#define SFFREE(freefunc, ptr) do { if (ptr) { freefunc(ptr); ptr = NULL; } } while (0)

#endif // __MACROS_H__
