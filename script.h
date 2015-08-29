/* Tcl in ~ 500 lines of code by Salvatore antirez Sanfilippo. BSD licensed */
#ifndef SCRIPT_H
#define SCRIPT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _MSC_VER
#define snprintf _snprintf
#define strdup _strdup
#endif

#include "scriptEval.h"


enum {SCRIPT_OK, SCRIPT_ERR, SCRIPT_RETURN, SCRIPT_BREAK, SCRIPT_CONTINUE};

struct scriptVar {
  char *name, *val;
  struct scriptVar *next;
};

struct scriptUpvar {//added
  char *name, *varName;
  struct scriptUpvar *next;
};

struct scriptInterp; /* forward declaration */
typedef int (*scriptCmdFunc)(struct scriptInterp *i, int argc, char **argv, const void *privdata);

struct scriptCmd {
  char *name;
  scriptCmdFunc func;
  void *privdata;
  struct scriptCmd *next;
};

struct scriptCallFrame {
  struct scriptVar *vars;
  struct scriptUpvar *upvars;//added
  struct scriptCallFrame *parent; /* parent is NULL at top level */
};

struct scriptInterp {
  int level; /* Level of nesting */
  struct scriptCallFrame *callframe;
  struct scriptCmd *commands;
  char *result;
};


#ifdef __cplusplus
extern "C" {
#endif

  void scriptInitInterp(struct scriptInterp *i);
  void scriptSetResult(struct scriptInterp *i, const char *s);
  int scriptSetVar(struct scriptInterp *i, const char *name, const char *val);
  int scriptSetUpvar(struct scriptInterp *i, const char *name, const char *varName);

  int scriptRegisterCommand(struct scriptInterp *i, const char *name, scriptCmdFunc f, void *privdata);
  int scriptCommandCallProc(struct scriptInterp *i, int argc, char **argv, const void *pd);
  struct scriptCmd *scriptGetCommand(struct scriptInterp *i, const char *name);
  struct scriptVar *scriptGetVar(struct scriptInterp *i, const char *name,
                             const char *val);

#ifdef __cplusplus
}
#endif

#endif
