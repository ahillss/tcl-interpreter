#ifndef SCRIPTEVAL_H
#define SCRIPTEVAL_H

#include "script.h"

#ifdef __cplusplus
extern "C" {
#endif

int scriptEval(struct scriptInterp *i,const char *text);

#ifdef __cplusplus
}
#endif

#endif
