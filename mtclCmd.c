#include "mtclCmd.h"
#include "mtclExpr.h"
#include "mtclEval.h"

int mtclArityErr(struct mtclInterp *i, const char *name) {
    char buf[1024];
    snprintf(buf,1024,"Wrong number of args for %s",name);
    mtclSetResult(i,buf);
    return MTCL_ERR;
}

int mtclCommandSet(struct mtclInterp *i, int argc, char **argv, const void *pd) {
  if(argc == 2) {
    struct mtclVar *v = mtclGetVar(i,argv[1],0);

    if(!v) {
      return MTCL_ERR;
    }

    mtclSetResult(i,v->val);
  } else if(argc == 3) {
    mtclSetVar(i,argv[1],argv[2]);
    mtclSetResult(i,argv[2]);
  } else {
    return mtclArityErr(i,argv[0]);
  }

  return MTCL_OK;
}

int mtclCommandPuts(struct mtclInterp *i, int argc, char **argv, const void *pd) {
  if(argc != 2) {
    return mtclArityErr(i,argv[0]);
  }

  printf("%s\n", argv[1]);
  return MTCL_OK;
}

int mtclCommandIf(struct mtclInterp *i, int argc, char **argv, const void *pd) {
  int retcode;

  if(argc != 3 && argc != 5) {
    return mtclArityErr(i,argv[0]);
  }



  if((retcode = mtclExpr(i,argv[1])) != MTCL_OK) {
    return retcode;
  }

  if(i->result[0]!='0' || i->result[1]!='\0') {
    return mtclEval(i,argv[2]);
  } else if (argc == 5) {
    return mtclEval(i,argv[4]);
  }

  return MTCL_OK;
}

int mtclCommandWhile(struct mtclInterp *i, int argc, char **argv, const void *pd) {
  if(argc != 3) {
    return mtclArityErr(i,argv[0]);
  }

  while(1) {
    int retcode = mtclExpr(i,argv[1]);

    if(retcode != MTCL_OK) {
      return retcode;
    }

    if(i->result[0]!='0' || i->result[1]!='\0') {
      if((retcode = mtclEval(i,argv[2])) == MTCL_CONTINUE) {
        continue;
      } else if(retcode == MTCL_OK) {
        continue;
      } else if(retcode == MTCL_BREAK) {
        return MTCL_OK;
      } else {
        return retcode;
      }
    } else {
      return MTCL_OK;
    }
  }
}

int mtclCommandRetCodes(struct mtclInterp *i, int argc, char **argv, const void *pd) {
  if(argc != 1) {
    return mtclArityErr(i,argv[0]);
  }

  if(strcmp(argv[0],"break") == 0) {
    return MTCL_BREAK;
  } else if(strcmp(argv[0],"continue") == 0) {
    return MTCL_CONTINUE;
  }

  return MTCL_OK;
}

int mtclCommandProc(struct mtclInterp *i, int argc, char **argv, const void *pd) {
  char **procdata = (char**)malloc(sizeof(char*)*2);

  if(argc != 4) {
    return mtclArityErr(i,argv[0]);
  }

  procdata[0] = strdup(argv[2]); /* arguments list */
  procdata[1] = strdup(argv[3]); /* procedure body */

  // return 0;
  return mtclRegisterCommand(i,argv[1],mtclCommandCallProc,procdata);
}

int mtclCommandReturn(struct mtclInterp *i, int argc, char **argv, const void *pd) {
  if(argc != 1 && argc != 2) {
    return mtclArityErr(i,argv[0]);
  }

  mtclSetResult(i, (argc == 2) ? argv[1] : "");
  return MTCL_RETURN;
}

int mtclCommandUpvar(struct mtclInterp *i, int argc, char **argv, const void *pd) {
  //tcl: upvar ?level? otherVar myVar ?otherVar myVar ...?
  //simple: upvar otherVar myVar

  if(argc != 3) {
    return mtclArityErr(i,argv[0]);
  }

  int retcode=mtclSetUpvar(i,argv[2],argv[1]);
  if(retcode==MTCL_OK) {
    mtclSetResult(i,"");
  }

  return retcode;

}

int mtclCommandUplevel(struct mtclInterp *i, int argc, char **argv, const void *pd) {
  //tcl: uplevel ?level? arg ?arg ...?
  //simple:  uplevel arg


  if(argc != 2) {
    return mtclArityErr(i,argv[0]);
  }

  if(!i->callframe->parent) {
    char errbuf[1024];
    snprintf(errbuf,1024,"error : uplevel '%s' called in global scope.",argv[1]);
    mtclSetResult(i,errbuf);
    return MTCL_ERR;
  }

  struct mtclCallFrame *tmpCf=i->callframe;

  i->callframe=i->callframe->parent;
  int retcode = mtclEval(i,argv[1]);
  i->callframe=tmpCf;

  if(retcode != MTCL_OK) {
    return retcode;
  }

  return MTCL_OK;
}


int mtclCommandExpr(struct mtclInterp *i, int argc, char **argv, const void *pd) {
  if(argc != 2) {
    return mtclArityErr(i,argv[0]);
  }

  return mtclExpr(i,argv[1]);
}

void mtclRegisterCoreCommands(struct mtclInterp *i) {
  mtclRegisterCommand(i,"set",mtclCommandSet,NULL);
  mtclRegisterCommand(i,"puts",mtclCommandPuts,NULL);
  mtclRegisterCommand(i,"if",mtclCommandIf,NULL);
  mtclRegisterCommand(i,"while",mtclCommandWhile,NULL);
  mtclRegisterCommand(i,"break",mtclCommandRetCodes,NULL);
  mtclRegisterCommand(i,"continue",mtclCommandRetCodes,NULL);
  mtclRegisterCommand(i,"proc",mtclCommandProc,NULL);
  mtclRegisterCommand(i,"return",mtclCommandReturn,NULL);

  mtclRegisterCommand(i,"upvar",mtclCommandUpvar,NULL);
  mtclRegisterCommand(i,"uplevel",mtclCommandUplevel,NULL);

  mtclRegisterCommand(i,"expr",mtclCommandExpr,NULL);


}
