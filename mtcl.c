#include "mtcl.h"
#include "mtclEval.h"


void mtclInitInterp(struct mtclInterp *i) {
    i->level = 0;
    i->callframe = (struct mtclCallFrame*)malloc(sizeof(struct mtclCallFrame));
    i->callframe->vars = NULL;
    i->callframe->upvars = NULL; //added
    i->callframe->parent = NULL;
    i->commands = NULL;
    i->result = strdup("");
}

void mtclUninitInterp(struct mtclInterp *i) {
  struct mtclCallFrame *cf=i->callframe;
  struct mtclCmd *cmd=i->commands;

  //free callframes
  while(cf) {
    struct mtclCallFrame *cfParent=cf->parent;
    struct mtclVar *var=cf->vars;
    struct mtclUpvar *upvar=cf->upvars;

    //free vars
    while(var) {
      struct mtclVar *varNext=var->next;
      free(var->name);
      free(var->val);
      free(var);
      var=varNext;
    }

    //free upvars
    while(upvar) {
      struct mtclUpvar *upvarNext=upvar->next;
      free(upvar->name);
      free(upvar->varName);
      free(upvar);
      upvar=upvarNext;
    }

    //
    free(cf);
    cf=cfParent;
  }

  //free commands
  while(cmd) {
    struct mtclCmd *cmdNext=cmd->next;
    free(cmd->name);
    free(cmd->privdata);
    free(cmd);
    cmd=cmdNext;
  }

  //free result
  free(i->result);
}

void mtclSetResult(struct mtclInterp *i, const char *s) {
    free(i->result);
    i->result = strdup(s);
}

struct mtclUpvar *mtclGetUpvar(struct mtclInterp *i,const char *name) {
  struct mtclUpvar *uv = i->callframe->upvars;

  while(uv) {
    if (strcmp(uv->name,name) == 0) {
      return uv;
    }

    uv = uv->next;
  }

  return NULL;
}

struct mtclVar *mtclGetVar(struct mtclInterp *i, const char *name,
                             const char *val) {
  struct mtclVar *v;
  struct mtclCallFrame *tmpCf=i->callframe;
  const char *varName=name;
  struct mtclUpvar *uv;

  //follow upvars
  while((uv = mtclGetUpvar(i,name))) {
    i->callframe=i->callframe->parent;
    name=uv->varName;

    if(!i->callframe){
      //report error ...
      //should catch setting upvars in global scope so this code is never called
      i->callframe=tmpCf;
      return NULL;
    }
  }

  //var found
  v = i->callframe->vars;

  while(v) {
    if (strcmp(v->name,name) == 0) {
      //set value
      if(val) {
        free(v->val);
        v->val = strdup(val);
      }

      //
      i->callframe=tmpCf;
      return v;
    }
    v = v->next;
  }

  //no var found, create/set value
  if(val) {
    v = (struct mtclVar*)malloc(sizeof(*v));
    v->name = strdup(name);
    v->val = strdup(val);
    v->next = i->callframe->vars;
    i->callframe->vars = v;
  }

  i->callframe=tmpCf;
  return NULL;
}

int mtclSetVar(struct mtclInterp *i, const char *name, const char *val) {
  struct mtclVar *v = mtclGetVar(i,name,val);
  return MTCL_OK;
}

int mtclSetUpvar(struct mtclInterp *i, const char *name, const char *varName) {

    if(!i->callframe->parent) {
      char errbuf[1024];
      snprintf(errbuf,1024,"error : upvar '%s %s' called in global scope.",varName,name);
      mtclSetResult(i,errbuf);
      return MTCL_ERR;
    }

    struct mtclUpvar *uv = mtclGetUpvar(i,name);
    if(uv) {
      free(uv->varName);
    } else {
      uv = (struct mtclUpvar*)malloc(sizeof(*uv));
      uv->name = strdup(name);
      uv->next = i->callframe->upvars;
      i->callframe->upvars = uv;
    }

    uv->varName = strdup(varName);
    return MTCL_OK;
}

struct mtclCmd *mtclGetCommand(struct mtclInterp *i, const char *name) {
    struct mtclCmd *c = i->commands;
    while(c) {
        if (strcmp(c->name,name) == 0) return c;
        c = c->next;
    }
    return NULL;
}

int mtclRegisterCommand(struct mtclInterp *i, const char *name, mtclCmdFunc f, void *privdata) {
    struct mtclCmd *c = mtclGetCommand(i,name);
    char errbuf[1024];
    if (c) {
        snprintf(errbuf,1024,"Command '%s' already defined",name);
        mtclSetResult(i,errbuf);
        return MTCL_ERR;
    }
    c = (struct mtclCmd*)malloc(sizeof(*c));
    c->name = strdup(name);
    c->func = f;
    c->privdata = privdata;
    c->next = i->commands;
    i->commands = c;
    return MTCL_OK;
}

/* ACTUAL COMMANDS! */


void mtclDropCallFrame(struct mtclInterp *i) {
    struct mtclCallFrame *cf = i->callframe;
    struct mtclVar *v = cf->vars, *t;
    while(v) {
        t = v->next;
        free(v->name);
        free(v->val);
        free(v);
        v = t;
    }
    i->callframe = cf->parent;
    free(cf);
}

int mtclCommandCallProc(struct mtclInterp *i, int argc, char **argv, const void *pd) {
  const char **x=(const char**)pd, *alist=x[0], *body=x[1];
  char *p=strdup(alist), *tofree;

    struct mtclCallFrame *cf = (struct mtclCallFrame*)malloc(sizeof(*cf));
    int arity = 0, done = 0, errcode = MTCL_OK;
    char errbuf[1024];
    cf->vars = NULL;
    cf->upvars=NULL;//added
    cf->parent = i->callframe;
    i->callframe = cf;
    tofree = p;
    while(1) {
        char *start = p;
        while(*p != ' ' && *p != '\0') p++;
        if (*p != '\0' && p == start) {
            p++; continue;
        }
        if (p == start) break;
        if (*p == '\0') done=1; else *p = '\0';
        if (++arity > argc-1) goto arityerr;
        mtclSetVar(i,start,argv[arity]);
        p++;
        if (done) break;
    }
    free(tofree);
    if (arity != argc-1) goto arityerr;
    errcode = mtclEval(i,body);
    if (errcode == MTCL_RETURN) errcode = MTCL_OK;
    mtclDropCallFrame(i); /* remove the called proc callframe */
    return errcode;
arityerr:
    snprintf(errbuf,1024,"Proc '%s' called with wrong arg num",argv[0]);
    mtclSetResult(i,errbuf);
    mtclDropCallFrame(i); /* remove the called proc callframe */
    return MTCL_ERR;
}
