#ifndef COMMANDS_H
#define COMMANDS_H

#include "script.h"
#include "scriptExpr.h"

#ifdef __cplusplus
extern "C" {
#endif

void scriptRegisterCoreCommands(struct scriptInterp *i);

#ifdef __cplusplus
}
#endif

#endif
