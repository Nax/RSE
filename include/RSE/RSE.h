#ifndef RSE_H
#define RSE_H 1

#include <RSE/abi.h>

typedef struct RseContext_ RseContext;

/*
 * init.c
 */
RSE_API RseContext* rseCreateContext(int frequency, int channels);
RSE_API void        rseDestroyContext(RseContext* ctx);

#endif
