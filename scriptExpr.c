#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <float.h>

#ifdef _MSC_VER
#define snprintf _snprintf
#endif

#include "scriptExprParse.h"
#include "scriptExpr.h"

enum {SCRIPT_EXPR_VAL_NONE,SCRIPT_EXPR_VAL_STR,
      SCRIPT_EXPR_VAL_INT,SCRIPT_EXPR_VAL_FLOAT};

typedef bool (*scriptExprOpFunc)(struct scriptExprInfo*);

struct scriptExprVal {
  union {double f;int i;char *s;} data;
  int type;
};

struct scriptExprOp {
  struct scriptExprOp *next;
  scriptExprOpFunc func;
  void *data;
  int argInd;

};

struct scriptExprInfo {
  struct scriptInterp *i;
  char *text;
  char errbuf[1024];
  int retcode;
  char *curWord,*result;
  struct scriptExprOp *opStk;
};

bool scriptExprPushOp(const char *name,const char *opName,
                     scriptExprOpFunc func,struct scriptExprInfo *info) {

  if(strncmp(name,opName,strlen(name))!=0) {
    return false;
  }

  struct scriptExprOp *op;
  op=(struct scriptExprOp*)malloc(sizeof(struct scriptExprOp));

  op->data=0;
  op->func=func;
  op->argInd=0;

  op->next=info->opStk;
  info->opStk=op;

  return true;
}

bool scriptExprPopOp(struct scriptExprInfo *info) {
  struct scriptExprOp *tmp=info->opStk;

  if(!tmp) {
    return false;
  }

  info->opStk=info->opStk->next;

  free(tmp->data);
  free(tmp);

  return true;
}

void scriptExprCurWordSetDouble(struct scriptExprInfo *info, double d) {
  size_t len=3+DBL_MANT_DIG-DBL_MIN_EXP + 1;
  info->curWord=(char*)malloc(len);
  snprintf(info->curWord,len,"%g",d);
}

double scriptExprCurWordGetDouble(struct scriptExprInfo *info) {
  double d=atof(info->curWord);
  free(info->curWord);
  info->curWord=0;
  return d;
}

void scriptExprCurWordSetInt(struct scriptExprInfo *info, int n) {
  size_t len=1+10 + 1;
  info->curWord=(char*)malloc(len);
  snprintf(info->curWord,len,"%i",n);
}


bool scriptExprAnd(struct scriptExprInfo *info) {

  return true;
}

bool scriptExprOr(struct scriptExprInfo *info) {
  return true;
}

bool scriptExprEq(struct scriptExprInfo *info) {
  if(info->opStk->argInd==0) {
    info->opStk->data=malloc(sizeof(double));
    *((double*)info->opStk->data)=scriptExprCurWordGetDouble(info);
    info->opStk->argInd++;
  } else {
    int r=*((double*)info->opStk->data)==scriptExprCurWordGetDouble(info);
    scriptExprCurWordSetInt(info,r);
    scriptExprPopOp(info);
  }

  return true;
}

bool scriptExprNe(struct scriptExprInfo *info) {
  if(info->opStk->argInd==0) {
    info->opStk->data=malloc(sizeof(double));
    *((double*)info->opStk->data)=scriptExprCurWordGetDouble(info);
    info->opStk->argInd++;
  } else {
    int r=*((double*)info->opStk->data)!=scriptExprCurWordGetDouble(info);
    scriptExprCurWordSetInt(info,r);
    scriptExprPopOp(info);
  }

  return true;
}

bool scriptExprLe(struct scriptExprInfo *info) {
  if(info->opStk->argInd==0) {
    info->opStk->data=malloc(sizeof(double));
    *((double*)info->opStk->data)=scriptExprCurWordGetDouble(info);
    info->opStk->argInd++;
  } else {
    int r=*((double*)info->opStk->data)<=scriptExprCurWordGetDouble(info);
    scriptExprCurWordSetInt(info,r);
    scriptExprPopOp(info);
  }

  return true;
}

bool scriptExprGe(struct scriptExprInfo *info) {
  if(info->opStk->argInd==0) {
    info->opStk->data=malloc(sizeof(double));
    *((double*)info->opStk->data)=scriptExprCurWordGetDouble(info);
    info->opStk->argInd++;
  } else {
    int r=*((double*)info->opStk->data)>=scriptExprCurWordGetDouble(info);
    scriptExprCurWordSetInt(info,r);
    scriptExprPopOp(info);
  }

  return true;
}

bool scriptExprGt(struct scriptExprInfo *info) {
  if(info->opStk->argInd==0) {
    info->opStk->data=malloc(sizeof(double));
    *((double*)info->opStk->data)=scriptExprCurWordGetDouble(info);
    info->opStk->argInd++;
  } else {
    int r=*((double*)info->opStk->data)>scriptExprCurWordGetDouble(info);
    scriptExprCurWordSetInt(info,r);
    scriptExprPopOp(info);
  }

  return true;
}

bool scriptExprLt(struct scriptExprInfo *info) {
  if(info->opStk->argInd==0) {
    info->opStk->data=malloc(sizeof(double));
    *((double*)info->opStk->data)=scriptExprCurWordGetDouble(info);
    info->opStk->argInd++;
  } else {
    int r=*((double*)info->opStk->data)<scriptExprCurWordGetDouble(info);
    scriptExprCurWordSetInt(info,r);
    scriptExprPopOp(info);
  }

  return true;
}

bool scriptExprNot(struct scriptExprInfo *info) {
  return true;
}

bool scriptExprAdd(struct scriptExprInfo *info) {
  if(info->opStk->argInd==0) {
    info->opStk->data=malloc(sizeof(double));
    *((double*)info->opStk->data)=scriptExprCurWordGetDouble(info);
    info->opStk->argInd++;
  } else {
    *((double*)info->opStk->data)+=scriptExprCurWordGetDouble(info);
    scriptExprCurWordSetDouble(info,*((double*)info->opStk->data));
    scriptExprPopOp(info);
  }

  return true;
}

bool scriptExprSub(struct scriptExprInfo *info) {
  if(info->opStk->argInd==0) {
    info->opStk->data=malloc(sizeof(double));
    *((double*)info->opStk->data)=scriptExprCurWordGetDouble(info);
    info->opStk->argInd++;
  } else {
    *((double*)info->opStk->data)-=scriptExprCurWordGetDouble(info);
    scriptExprCurWordSetDouble(info,*((double*)info->opStk->data));
    scriptExprPopOp(info);
  }

  return true;
}

bool scriptExprMul(struct scriptExprInfo *info) {
  if(info->opStk->argInd==0) {
    info->opStk->data=malloc(sizeof(double));
    *((double*)info->opStk->data)=scriptExprCurWordGetDouble(info);
    info->opStk->argInd++;
  } else {
    *((double*)info->opStk->data)*=scriptExprCurWordGetDouble(info);
    scriptExprCurWordSetDouble(info,*((double*)info->opStk->data));
    scriptExprPopOp(info);
  }

  return true;
}

bool scriptExprDiv(struct scriptExprInfo *info) {
  if(info->opStk->argInd==0) {
    info->opStk->data=malloc(sizeof(double));
    *((double*)info->opStk->data)=scriptExprCurWordGetDouble(info);
    info->opStk->argInd++;
  } else {
    *((double*)info->opStk->data)/=scriptExprCurWordGetDouble(info);
    scriptExprCurWordSetDouble(info,*((double*)info->opStk->data));
    scriptExprPopOp(info);
  }

  return true;
}


void scriptExprAppendCurWord(struct scriptExprInfo *info,
                            const char *a,const char *b) {
  size_t m=(b-a);
  size_t n=info->curWord?strlen(info->curWord):0;
  info->curWord=(char*)realloc(info->curWord,n+m+1);
  memcpy(&info->curWord[n],a,m);
  info->curWord[n+m]='\0';
}

bool scriptExprParsePartCallback(void *data,const char *a,const char *b) {
  //on receiving part of a word
#ifdef SCRIPT_EXPR_DEBUG
  printf("%.*s",(int)(b-a),a);
#else
  struct scriptExprInfo *info;
  info=(struct scriptExprInfo*)data;

  scriptExprAppendCurWord(info,a,b);

  info->retcode=SCRIPT_OK; //probably not necessary
#endif

  return true;
}

bool scriptExprParseVarCallback(void *data,const char *a,const char *b) {
  //on receiving a var part of a word
#ifdef SCRIPT_EXPR_DEBUG
  printf("${%.*s}",(int)(b-a),a);
#else
  struct scriptExprInfo *info;
  info=(struct scriptExprInfo*)data;


  size_t tmpLen=b-a;
  char *tmp=(char*)malloc(tmpLen+1);
  memcpy(tmp,a,tmpLen);
  tmp[tmpLen]='\0';

  struct scriptVar *pv=scriptGetVar(info->i,tmp,NULL);

  if(!pv) {
    snprintf(info->errbuf,1024,"No such variable '%s'",tmp);
    scriptSetResult(info->i,info->errbuf);
    info->retcode=SCRIPT_ERR;
    return false;
  }

  scriptExprAppendCurWord(info,pv->val,pv->val+strlen(pv->val));
  free(tmp);
  info->retcode=SCRIPT_OK; //probably not necessary
#endif

  return true;
}

bool scriptExprParseCmdCallback(void *data,const char *a,const char *b) {
  //on receiving a cmd part of a word
#ifdef SCRIPT_EXPR_DEBUG
  printf("[%.*s]",(int)(b-a),a);
#else
  struct scriptExprInfo *info;
  info=(struct scriptExprInfo*)data;

  size_t tmpLen=b-a;
  char *tmp=(char*)malloc(tmpLen+1);
  memcpy(tmp,a,tmpLen);
  tmp[tmpLen]='\0';

  info->retcode=scriptEval(info->i,tmp);
  free(tmp);

  //on return/break/continue status it must stop evaluating
  if(info->retcode != SCRIPT_OK) {
    return false;
  }

  scriptExprAppendCurWord(info,info->i->result,
                         info->i->result+strlen(info->i->result));
#endif

  return true;
}


bool scriptExprParseWordEndCallback(void *data) {
  //on end of word
#ifdef SCRIPT_EXPR_DEBUG
  printf("\n");
#else
  struct scriptExprInfo *info;
  info=(struct scriptExprInfo*)data;

  while(info->curWord) {
    if(info->opStk) {
      info->opStk->func(info);
    } else {
      free(info->result);
      info->result=strdup(info->curWord);

      free(info->curWord);
      info->curWord=0;
    }

  }
#endif

  return true;
}

bool scriptExprParseMathEndCallback(void *data,const char *a,const char *b) {
  //on end of math word
#ifdef SCRIPT_EXPR_DEBUG
  printf("[%.*s]\n",(int)(b-a),a);
  return true;
#else
  struct scriptExprInfo *info;
  info=(struct scriptExprInfo*)data;
  info->retcode=SCRIPT_OK;


  if(scriptExprPushOp("&&",a,scriptExprAnd,info) |
     scriptExprPushOp("||",a,scriptExprOr,info) |
     scriptExprPushOp("==",a,scriptExprEq,info) |
     scriptExprPushOp("!=",a,scriptExprNe,info) |
     scriptExprPushOp(">=",a,scriptExprGe,info) |
     scriptExprPushOp("<=",a,scriptExprLe,info) |
     scriptExprPushOp(">",a,scriptExprGt,info) |
     scriptExprPushOp("<",a,scriptExprLt,info) |
     scriptExprPushOp("+",a,scriptExprAdd,info) |
     scriptExprPushOp("-",a,scriptExprSub,info) |
     scriptExprPushOp("*",a,scriptExprMul,info) |
     scriptExprPushOp("/",a,scriptExprDiv,info)) {
    return true;
  }

  snprintf(info->errbuf,1024,"Expr symbol not implemented '%.*s'",(int)(b-a),a);
  scriptSetResult(info->i,info->errbuf);
  info->retcode=SCRIPT_ERR;
  return false;
#endif
}

void scriptExprParseErr(const char *lbl,struct scriptExprInfo *info,const char *p) {
  int row=1,col=1;
  const char *x=info->text;
  const char *start=info->text;
  const char *end=p;

  while(end[0]!='\0' && end[0]!='\n' && (end[0]!='\r' || end[1]!='\n')) {
    end++;
  }

  while(x!=p) {
    if(x[0]=='\n') {
      row++;
      col=1;
      start=x+1;
    } else {
      col++;
    }

    x++;
  }

  printf("%s at line %i, col %i:\n",lbl,row,col);
  printf("'%.*s'\n",(int)(end-start),start);
  printf("%*s%s\n", col, "", "^");
}

void scriptExprParseErrCallback(void *data,const char *p) {
  struct scriptExprInfo *info;
  info=(struct scriptExprInfo*)data;
  printf("expr parse err\n");
  // scriptExprParseErr("parse error",info,p);
  //todo
}

void scriptExprParseParenErrCallback(void *data,const char *p) {
  struct scriptExprInfo *info;
  info=(struct scriptExprInfo*)data;
  printf("expr parse err\n");
  // scriptExprParseErr("no matching paren error",info,p);
  //todo
}

void scriptExprParseRunErrCallback(void *data,const char *p) {
  struct scriptEvalInfo *info;
  info=(struct scriptEvalInfo*)data;
  printf("expr parse err\n");
  // scriptExprParseErr("runerr",info,p);
  //todo
}

int scriptExpr(struct scriptInterp *i, const char *text) {
  struct scriptExprInfo info;
  struct scriptExprOp *op;

  //init
  info.i=i;
  info.text=strdup(text);
  info.curWord=0;
  info.result=0;
  info.opStk=0;
  info.retcode=SCRIPT_OK;

  //parse

  scriptExprParse(info.text,(void*)(&info));

  //result
  if(info.result && info.retcode==SCRIPT_OK && !info.opStk) {
    scriptSetResult(i,info.result);
  } else if(info.opStk) {
    info.retcode=SCRIPT_ERR;
    scriptSetResult(info.i,"expr, not enough args for operation");
  }

  //cleanup
  while(scriptExprPopOp(&info));
  free(info.curWord);
  free(info.result);
  free(info.text);

  //
  return info.retcode;
}
