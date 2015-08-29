#include "scriptCmd.h"

int scriptArityErr(struct scriptInterp *i, const char *name) {
    char buf[1024];
    snprintf(buf,1024,"Wrong number of args for %s",name);
    scriptSetResult(i,buf);
    return SCRIPT_ERR;
}

int scriptCommandSet(struct scriptInterp *i, int argc, char **argv, const void *pd) {
  if(argc == 2) {
    struct scriptVar *v = scriptGetVar(i,argv[1],0);

    if(!v) {
      return SCRIPT_ERR;
    }

    scriptSetResult(i,v->val);
  } else if(argc == 3) {
    scriptSetVar(i,argv[1],argv[2]);
    scriptSetResult(i,argv[2]);
  } else {
    return scriptArityErr(i,argv[0]);
  }

  return SCRIPT_OK;
}

int scriptCommandPuts(struct scriptInterp *i, int argc, char **argv, const void *pd) {
  if(argc != 2) {
    return scriptArityErr(i,argv[0]);
  }

  printf("%s\n", argv[1]);
  return SCRIPT_OK;
}

int scriptCommandIf(struct scriptInterp *i, int argc, char **argv, const void *pd) {
  int retcode;

  if(argc != 3 && argc != 5) {
    return scriptArityErr(i,argv[0]);
  }



  if((retcode = scriptExpr(i,argv[1])) != SCRIPT_OK) {
    return retcode;
  }

  if(i->result[0]!='0' || i->result[1]!='\0') {
    return scriptEval(i,argv[2]);
  } else if (argc == 5) {
    return scriptEval(i,argv[4]);
  }

  return SCRIPT_OK;
}

int scriptCommandWhile(struct scriptInterp *i, int argc, char **argv, const void *pd) {
  if(argc != 3) {
    return scriptArityErr(i,argv[0]);
  }

  while(1) {
    int retcode = scriptExpr(i,argv[1]);

    if(retcode != SCRIPT_OK) {
      return retcode;
    }

    if(i->result[0]!='0' || i->result[1]!='\0') {
      if((retcode = scriptEval(i,argv[2])) == SCRIPT_CONTINUE) {
        continue;
      } else if(retcode == SCRIPT_OK) {
        continue;
      } else if(retcode == SCRIPT_BREAK) {
        return SCRIPT_OK;
      } else {
        return retcode;
      }
    } else {
      return SCRIPT_OK;
    }
  }
}

int scriptCommandRetCodes(struct scriptInterp *i, int argc, char **argv, const void *pd) {
  if(argc != 1) {
    return scriptArityErr(i,argv[0]);
  }

  if(strcmp(argv[0],"break") == 0) {
    return SCRIPT_BREAK;
  } else if(strcmp(argv[0],"continue") == 0) {
    return SCRIPT_CONTINUE;
  }

  return SCRIPT_OK;
}

int scriptCommandProc(struct scriptInterp *i, int argc, char **argv, const void *pd) {
  char **procdata = (char**)malloc(sizeof(char*)*2);

  if(argc != 4) {
    return scriptArityErr(i,argv[0]);
  }

  procdata[0] = strdup(argv[2]); /* arguments list */
  procdata[1] = strdup(argv[3]); /* procedure body */

  // return 0;
  return scriptRegisterCommand(i,argv[1],scriptCommandCallProc,procdata);
}

int scriptCommandReturn(struct scriptInterp *i, int argc, char **argv, const void *pd) {
  if(argc != 1 && argc != 2) {
    return scriptArityErr(i,argv[0]);
  }

  scriptSetResult(i, (argc == 2) ? argv[1] : "");
  return SCRIPT_RETURN;
}

int scriptCommandUpvar(struct scriptInterp *i, int argc, char **argv, const void *pd) {
  //tcl: upvar ?level? otherVar myVar ?otherVar myVar ...?
  //simple: upvar otherVar myVar

  if(argc != 3) {
    return scriptArityErr(i,argv[0]);
  }

  int retcode=scriptSetUpvar(i,argv[2],argv[1]);
  if(retcode==SCRIPT_OK) {
    scriptSetResult(i,"");
  }

  return retcode;

}

int scriptCommandUplevel(struct scriptInterp *i, int argc, char **argv, const void *pd) {
  //tcl: uplevel ?level? arg ?arg ...?
  //simple:  uplevel arg


  if(argc != 2) {
    return scriptArityErr(i,argv[0]);
  }

  if(!i->callframe->parent) {
    char errbuf[1024];
    snprintf(errbuf,1024,"error : uplevel '%s' called in global scope.",argv[1]);
    scriptSetResult(i,errbuf);
    return SCRIPT_ERR;
  }

  struct scriptCallFrame *tmpCf=i->callframe;

  i->callframe=i->callframe->parent;
  int retcode = scriptEval(i,argv[1]);
  i->callframe=tmpCf;

  if(retcode != SCRIPT_OK) {
    return retcode;
  }

  return SCRIPT_OK;
}


int scriptCommandExpr(struct scriptInterp *i, int argc, char **argv, const void *pd) {
  if(argc != 2) {
    return scriptArityErr(i,argv[0]);
  }

  return scriptExpr(i,argv[1]);
}

void scriptRegisterCoreCommands(struct scriptInterp *i) {
  scriptRegisterCommand(i,"set",scriptCommandSet,NULL);
  scriptRegisterCommand(i,"puts",scriptCommandPuts,NULL);
  scriptRegisterCommand(i,"if",scriptCommandIf,NULL);
  scriptRegisterCommand(i,"while",scriptCommandWhile,NULL);
  scriptRegisterCommand(i,"break",scriptCommandRetCodes,NULL);
  scriptRegisterCommand(i,"continue",scriptCommandRetCodes,NULL);
  scriptRegisterCommand(i,"proc",scriptCommandProc,NULL);
  scriptRegisterCommand(i,"return",scriptCommandReturn,NULL);

  scriptRegisterCommand(i,"upvar",scriptCommandUpvar,NULL);
  scriptRegisterCommand(i,"uplevel",scriptCommandUplevel,NULL);

  scriptRegisterCommand(i,"expr",scriptCommandExpr,NULL);


}
