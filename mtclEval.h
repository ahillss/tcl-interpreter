#ifndef MTCLEVAL_H
#define MTCLEVAL_H

#include "mtcl.h"

#ifdef __cplusplus
extern "C" {
#endif

int mtclEval(struct mtclInterp *i,const char *text);

#ifdef __cplusplus
}
#endif

#endif
