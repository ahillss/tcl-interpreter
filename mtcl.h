/* Tcl in ~ 500 lines of code by Salvatore antirez Sanfilippo. BSD licensed */
#ifndef MTCL_H
#define MTCL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _MSC_VER
#define snprintf _snprintf
#define strdup _strdup
#endif


enum {MTCL_OK, MTCL_ERR, MTCL_RETURN, MTCL_BREAK, MTCL_CONTINUE};

struct mtclVar {
  char *name, *val;
  struct mtclVar *next;
};

struct mtclUpvar {//added
  char *name, *varName;
  struct mtclUpvar *next;
};

struct mtclInterp; /* forward declaration */
typedef int (*mtclCmdFunc)(struct mtclInterp *i, int argc, char **argv, const void *privdata);

struct mtclCmd {
  char *name;
  mtclCmdFunc func;
  void *privdata;
  struct mtclCmd *next;
};

struct mtclCallFrame {
  struct mtclVar *vars;
  struct mtclUpvar *upvars;//added
  struct mtclCallFrame *parent; /* parent is NULL at top level */
};

struct mtclInterp {
  int level; /* Level of nesting */
  struct mtclCallFrame *callframe;
  struct mtclCmd *commands;
  char *result;
};


#ifdef __cplusplus
extern "C" {
#endif

  void mtclInitInterp(struct mtclInterp *i);
  void mtclUninitInterp(struct mtclInterp *i);
  void mtclSetResult(struct mtclInterp *i, const char *s);
  int mtclSetVar(struct mtclInterp *i, const char *name, const char *val);
  int mtclSetUpvar(struct mtclInterp *i, const char *name, const char *varName);

  int mtclRegisterCommand(struct mtclInterp *i, const char *name,
                          mtclCmdFunc f, void *privdata);
  int mtclCommandCallProc(struct mtclInterp *i, int argc, char **argv,
                          const void *pd);
  struct mtclCmd *mtclGetCommand(struct mtclInterp *i, const char *name);
  struct mtclVar *mtclGetVar(struct mtclInterp *i, const char *name,
                             const char *val);

#ifdef __cplusplus
}
#endif

#endif
