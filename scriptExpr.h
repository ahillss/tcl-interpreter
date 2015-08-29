#ifndef SCRIPTEXPR_H
#define SCRIPTEXPR_H

#include "script.h"

#ifdef __cplusplus
extern "C" {
#endif

  int scriptExpr(struct scriptInterp *i, const char *text);

#ifdef __cplusplus
}
#endif

#endif
