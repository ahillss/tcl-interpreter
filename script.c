#include "script.h"


void scriptInitInterp(struct scriptInterp *i) {
    i->level = 0;
    i->callframe = (struct scriptCallFrame*)malloc(sizeof(struct scriptCallFrame));
    i->callframe->vars = NULL;
    i->callframe->upvars = NULL; //added
    i->callframe->parent = NULL;
    i->commands = NULL;
    i->result = strdup("");
}

void scriptSetResult(struct scriptInterp *i, const char *s) {
    free(i->result);
    i->result = strdup(s);
}

struct scriptUpvar *scriptGetUpvar(struct scriptInterp *i,const char *name) {
  struct scriptUpvar *uv = i->callframe->upvars;

  while(uv) {
    if (strcmp(uv->name,name) == 0) {
      return uv;
    }

    uv = uv->next;
  }

  return NULL;
}

struct scriptVar *scriptGetVar(struct scriptInterp *i, const char *name,
                             const char *val) {
  struct scriptVar *v;
  struct scriptCallFrame *tmpCf=i->callframe;
  const char *varName=name;
  struct scriptUpvar *uv;

  //follow upvars
  while(uv = scriptGetUpvar(i,name)) {
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
    v = (struct scriptVar*)malloc(sizeof(*v));
    v->name = strdup(name);
    v->val = strdup(val);
    v->next = i->callframe->vars;
    i->callframe->vars = v;
  }

  i->callframe=tmpCf;
  return NULL;
}

int scriptSetVar(struct scriptInterp *i, const char *name, const char *val) {
  struct scriptVar *v = scriptGetVar(i,name,val);
  return SCRIPT_OK;
}

int scriptSetUpvar(struct scriptInterp *i, const char *name, const char *varName) {

    if(!i->callframe->parent) {
      char errbuf[1024];
      snprintf(errbuf,1024,"error : upvar '%s %s' called in global scope.",varName,name);
      scriptSetResult(i,errbuf);
      return SCRIPT_ERR;
    }

    struct scriptUpvar *uv = scriptGetUpvar(i,name);
    if(uv) {
      free(uv->varName);
    } else {
      uv = (struct scriptUpvar*)malloc(sizeof(*uv));
      uv->name = strdup(name);
      uv->next = i->callframe->upvars;
      i->callframe->upvars = uv;
    }

    uv->varName = strdup(varName);
    return SCRIPT_OK;
}

struct scriptCmd *scriptGetCommand(struct scriptInterp *i, const char *name) {
    struct scriptCmd *c = i->commands;
    while(c) {
        if (strcmp(c->name,name) == 0) return c;
        c = c->next;
    }
    return NULL;
}

int scriptRegisterCommand(struct scriptInterp *i, const char *name, scriptCmdFunc f, void *privdata) {
    struct scriptCmd *c = scriptGetCommand(i,name);
    char errbuf[1024];
    if (c) {
        snprintf(errbuf,1024,"Command '%s' already defined",name);
        scriptSetResult(i,errbuf);
        return SCRIPT_ERR;
    }
    c = (struct scriptCmd*)malloc(sizeof(*c));
    c->name = strdup(name);
    c->func = f;
    c->privdata = privdata;
    c->next = i->commands;
    i->commands = c;
    return SCRIPT_OK;
}

/* ACTUAL COMMANDS! */


void scriptDropCallFrame(struct scriptInterp *i) {
    struct scriptCallFrame *cf = i->callframe;
    struct scriptVar *v = cf->vars, *t;
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

int scriptCommandCallProc(struct scriptInterp *i, int argc, char **argv, const void *pd) {
  const char **x=(const char**)pd, *alist=x[0], *body=x[1];
  char *p=strdup(alist), *tofree;

    struct scriptCallFrame *cf = (struct scriptCallFrame*)malloc(sizeof(*cf));
    int arity = 0, done = 0, errcode = SCRIPT_OK;
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
        scriptSetVar(i,start,argv[arity]);
        p++;
        if (done) break;
    }
    free(tofree);
    if (arity != argc-1) goto arityerr;
    errcode = scriptEval(i,body);
    if (errcode == SCRIPT_RETURN) errcode = SCRIPT_OK;
    scriptDropCallFrame(i); /* remove the called proc callframe */
    return errcode;
arityerr:
    snprintf(errbuf,1024,"Proc '%s' called with wrong arg num",argv[0]);
    scriptSetResult(i,errbuf);
    scriptDropCallFrame(i); /* remove the called proc callframe */
    return SCRIPT_ERR;
}
