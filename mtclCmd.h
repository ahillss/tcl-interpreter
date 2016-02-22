#ifndef COMMANDS_H
#define COMMANDS_H

#include "mtcl.h"
#include "mtclExpr.h"

#ifdef __cplusplus
extern "C" {
#endif

void mtclRegisterCoreCommands(struct mtclInterp *i);

#ifdef __cplusplus
}
#endif

#endif
