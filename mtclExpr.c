#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <float.h>

#ifdef _MSC_VER
#define snprintf _snprintf
#endif

#include "mtclExprParse.h"
#include "mtclExpr.h"
#include "mtclEval.h"
#include "mtcl.h"

enum {MTCL_EXPR_VAL_NONE,MTCL_EXPR_VAL_STR,
      MTCL_EXPR_VAL_INT,MTCL_EXPR_VAL_FLOAT};

struct mtclExprInfo;

typedef bool (*mtclExprOpFunc)(struct mtclExprInfo*);

struct mtclExprVal {
  union {double f;int i;char *s;} data;
  int type;
};

struct mtclExprOp {
  struct mtclExprOp *next;
  mtclExprOpFunc func;
  void *data;
  int argInd;

};

struct mtclExprInfo {
  struct mtclInterp *i;
  char *text;
  char errbuf[1024];
  int retcode;
  char *curWord,*result;
  struct mtclExprOp *opStk;
};

bool mtclExprPushOp(const char *name,const char *a,const char *b,
                     mtclExprOpFunc func,struct mtclExprInfo *info) {

  // if(strncmp(name,opName,strlen(name))!=0) {
  //   return false;
  // }
  printf("'%.*s'\n",(int)(b-a),a);
  while(name[0]!='\0') {
    if(a==b || name[0]!=a[0]) {
      return false;
    }
    name++;
    a++;
  }

  struct mtclExprOp *op;
  op=(struct mtclExprOp*)malloc(sizeof(struct mtclExprOp));

  op->data=0;
  op->func=func;
  op->argInd=0;

  op->next=info->opStk;
  info->opStk=op;

  return true;
}

bool mtclExprPopOp(struct mtclExprInfo *info) {
  struct mtclExprOp *tmp=info->opStk;

  if(!tmp) {
    return false;
  }

  info->opStk=info->opStk->next;

  free(tmp->data);
  free(tmp);

  return true;
}

void mtclExprCurWordSetDouble(struct mtclExprInfo *info, double d) {
  size_t len=3+DBL_MANT_DIG-DBL_MIN_EXP + 1;
  info->curWord=(char*)malloc(len);
  snprintf(info->curWord,len,"%g",d);
}

double mtclExprCurWordGetDouble(struct mtclExprInfo *info) {
  double d=atof(info->curWord);
  free(info->curWord);
  info->curWord=0;
  return d;
}

void mtclExprCurWordSetInt(struct mtclExprInfo *info, int n) {
  size_t len=1+10 + 1;
  info->curWord=(char*)malloc(len);
  snprintf(info->curWord,len,"%i",n);
}


bool mtclExprAnd(struct mtclExprInfo *info) {

  return true;
}

bool mtclExprOr(struct mtclExprInfo *info) {
  return true;
}

bool mtclExprEq(struct mtclExprInfo *info) {
  if(info->opStk->argInd==0) {
    info->opStk->data=malloc(sizeof(double));
    *((double*)info->opStk->data)=mtclExprCurWordGetDouble(info);
    info->opStk->argInd++;
  } else {
    int r=*((double*)info->opStk->data)==mtclExprCurWordGetDouble(info);
    mtclExprCurWordSetInt(info,r);
    mtclExprPopOp(info);
  }

  return true;
}

bool mtclExprNe(struct mtclExprInfo *info) {
  if(info->opStk->argInd==0) {
    info->opStk->data=malloc(sizeof(double));
    *((double*)info->opStk->data)=mtclExprCurWordGetDouble(info);
    info->opStk->argInd++;
  } else {
    int r=*((double*)info->opStk->data)!=mtclExprCurWordGetDouble(info);
    mtclExprCurWordSetInt(info,r);
    mtclExprPopOp(info);
  }

  return true;
}

bool mtclExprLe(struct mtclExprInfo *info) {
  if(info->opStk->argInd==0) {
    info->opStk->data=malloc(sizeof(double));
    *((double*)info->opStk->data)=mtclExprCurWordGetDouble(info);
    info->opStk->argInd++;
  } else {
    int r=*((double*)info->opStk->data)<=mtclExprCurWordGetDouble(info);
    mtclExprCurWordSetInt(info,r);
    mtclExprPopOp(info);
  }

  return true;
}

bool mtclExprGe(struct mtclExprInfo *info) {
  if(info->opStk->argInd==0) {
    info->opStk->data=malloc(sizeof(double));
    *((double*)info->opStk->data)=mtclExprCurWordGetDouble(info);
    info->opStk->argInd++;
  } else {
    int r=*((double*)info->opStk->data)>=mtclExprCurWordGetDouble(info);
    mtclExprCurWordSetInt(info,r);
    mtclExprPopOp(info);
  }

  return true;
}

bool mtclExprGt(struct mtclExprInfo *info) {
  if(info->opStk->argInd==0) {
    info->opStk->data=malloc(sizeof(double));
    *((double*)info->opStk->data)=mtclExprCurWordGetDouble(info);
    info->opStk->argInd++;
  } else {
    int r=*((double*)info->opStk->data)>mtclExprCurWordGetDouble(info);
    mtclExprCurWordSetInt(info,r);
    mtclExprPopOp(info);
  }

  return true;
}

bool mtclExprLt(struct mtclExprInfo *info) {
  if(info->opStk->argInd==0) {
    info->opStk->data=malloc(sizeof(double));
    *((double*)info->opStk->data)=mtclExprCurWordGetDouble(info);
    info->opStk->argInd++;
  } else {
    int r=*((double*)info->opStk->data)<mtclExprCurWordGetDouble(info);
    mtclExprCurWordSetInt(info,r);
    mtclExprPopOp(info);
  }

  return true;
}

bool mtclExprNot(struct mtclExprInfo *info) {
  return true;
}

bool mtclExprAdd(struct mtclExprInfo *info) {
  if(info->opStk->argInd==0) {
    info->opStk->data=malloc(sizeof(double));
    *((double*)info->opStk->data)=mtclExprCurWordGetDouble(info);
    info->opStk->argInd++;
  } else {
    *((double*)info->opStk->data)+=mtclExprCurWordGetDouble(info);
    mtclExprCurWordSetDouble(info,*((double*)info->opStk->data));
    mtclExprPopOp(info);
  }

  return true;
}

bool mtclExprSub(struct mtclExprInfo *info) {
  if(info->opStk->argInd==0) {
    info->opStk->data=malloc(sizeof(double));
    *((double*)info->opStk->data)=mtclExprCurWordGetDouble(info);
    info->opStk->argInd++;
  } else {
    *((double*)info->opStk->data)-=mtclExprCurWordGetDouble(info);
    mtclExprCurWordSetDouble(info,*((double*)info->opStk->data));
    mtclExprPopOp(info);
  }

  return true;
}

bool mtclExprMul(struct mtclExprInfo *info) {
  if(info->opStk->argInd==0) {
    info->opStk->data=malloc(sizeof(double));
    *((double*)info->opStk->data)=mtclExprCurWordGetDouble(info);
    info->opStk->argInd++;
  } else {
    *((double*)info->opStk->data)*=mtclExprCurWordGetDouble(info);
    mtclExprCurWordSetDouble(info,*((double*)info->opStk->data));
    mtclExprPopOp(info);
  }

  return true;
}

bool mtclExprDiv(struct mtclExprInfo *info) {
  if(info->opStk->argInd==0) {
    info->opStk->data=malloc(sizeof(double));
    *((double*)info->opStk->data)=mtclExprCurWordGetDouble(info);
    info->opStk->argInd++;
  } else {
    *((double*)info->opStk->data)/=mtclExprCurWordGetDouble(info);
    mtclExprCurWordSetDouble(info,*((double*)info->opStk->data));
    mtclExprPopOp(info);
  }

  return true;
}


void mtclExprAppendCurWord(struct mtclExprInfo *info,
                            const char *a,const char *b) {
  size_t m=(b-a);
  size_t n=info->curWord?strlen(info->curWord):0;
  info->curWord=(char*)realloc(info->curWord,n+m+1);
  memcpy(&info->curWord[n],a,m);
  info->curWord[n+m]='\0';
}

bool mtclExprParsePartCallback(void *data,const char *a,const char *b) {
  //on receiving part of a word
#ifdef MTCL_EXPR_DEBUG
  printf("%.*s",(int)(b-a),a);
#else
  struct mtclExprInfo *info;
  info=(struct mtclExprInfo*)data;

  mtclExprAppendCurWord(info,a,b);

  info->retcode=MTCL_OK; //probably not necessary
#endif

  return true;
}

bool mtclExprParseVarCallback(void *data,const char *a,const char *b) {
  //on receiving a var part of a word
#ifdef MTCL_EXPR_DEBUG
  printf("${%.*s}",(int)(b-a),a);
#else
  struct mtclExprInfo *info;
  info=(struct mtclExprInfo*)data;


  size_t tmpLen=b-a;
  char *tmp=(char*)malloc(tmpLen+1);
  memcpy(tmp,a,tmpLen);
  tmp[tmpLen]='\0';

  struct mtclVar *pv=mtclGetVar(info->i,tmp,NULL);

  if(!pv) {
    snprintf(info->errbuf,1024,"No such variable '%s'",tmp);
    mtclSetResult(info->i,info->errbuf);
    info->retcode=MTCL_ERR;
    return false;
  }

  mtclExprAppendCurWord(info,pv->val,pv->val+strlen(pv->val));
  free(tmp);
  info->retcode=MTCL_OK; //probably not necessary
#endif

  return true;
}

bool mtclExprParseCmdCallback(void *data,const char *a,const char *b) {
  //on receiving a cmd part of a word
#ifdef MTCL_EXPR_DEBUG
  printf("[%.*s]",(int)(b-a),a);
#else
  struct mtclExprInfo *info;
  info=(struct mtclExprInfo*)data;

  size_t tmpLen=b-a;
  char *tmp=(char*)malloc(tmpLen+1);
  memcpy(tmp,a,tmpLen);
  tmp[tmpLen]='\0';

  info->retcode=mtclEval(info->i,tmp);
  free(tmp);

  //on return/break/continue status it must stop evaluating
  if(info->retcode != MTCL_OK) {
    return false;
  }

  mtclExprAppendCurWord(info,info->i->result,
                         info->i->result+strlen(info->i->result));
#endif

  return true;
}


bool mtclExprParseWordEndCallback(void *data) {
  //on end of word
#ifdef MTCL_EXPR_DEBUG
  printf("\n");
#else
  struct mtclExprInfo *info;
  info=(struct mtclExprInfo*)data;

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

bool mtclExprParseMathEndCallback(void *data,const char *a,const char *b) {
  //on end of math word
#ifdef MTCL_EXPR_DEBUG
  printf("[%.*s]\n",(int)(b-a),a);
  return true;
#else
  struct mtclExprInfo *info;
  info=(struct mtclExprInfo*)data;
  info->retcode=MTCL_OK;


  if(mtclExprPushOp("&&",a,b,mtclExprAnd,info) |
     mtclExprPushOp("||",a,b,mtclExprOr,info) |
     mtclExprPushOp("==",a,b,mtclExprEq,info) |
     mtclExprPushOp("!=",a,b,mtclExprNe,info) |
     mtclExprPushOp(">=",a,b,mtclExprGe,info) |
     mtclExprPushOp("<=",a,b,mtclExprLt,info) |
     mtclExprPushOp(">",a,b,mtclExprGt,info) |
     mtclExprPushOp("<",a,b,mtclExprLt,info) |
     mtclExprPushOp("+",a,b,mtclExprAdd,info) |
     mtclExprPushOp("-",a,b,mtclExprSub,info) |
     mtclExprPushOp("*",a,b,mtclExprMul,info) |
     mtclExprPushOp("/",a,b,mtclExprDiv,info)) {
    return true;
  }

  snprintf(info->errbuf,1024,"Expr symbol not implemented '%.*s'",(int)(b-a),a);
  mtclSetResult(info->i,info->errbuf);
  info->retcode=MTCL_ERR;
  return false;
#endif
}

void mtclExprParseErr(const char *lbl,struct mtclExprInfo *info,const char *p) {
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

void mtclExprParseErrCallback(void *data,const char *p) {
  struct mtclExprInfo *info;
  info=(struct mtclExprInfo*)data;
  printf("expr parse err\n");
  // mtclExprParseErr("parse error",info,p);
  //todo
}

void mtclExprParseParenErrCallback(void *data,const char *p) {
  struct mtclExprInfo *info;
  info=(struct mtclExprInfo*)data;
  printf("expr parse err\n");
  // mtclExprParseErr("no matching paren error",info,p);
  //todo
}

void mtclExprParseRunErrCallback(void *data,const char *p) {
  struct mtclEvalInfo *info;
  info=(struct mtclEvalInfo*)data;
  printf("expr parse err\n");
  // mtclExprParseErr("runerr",info,p);
  //todo
}

int mtclExpr(struct mtclInterp *i, const char *text) {
  struct mtclExprInfo info;
  struct mtclExprOp *op;

  //init
  info.i=i;
  info.text=strdup(text);
  info.curWord=0;
  info.result=0;
  info.opStk=0;
  info.retcode=MTCL_OK;

  //parse

  mtclExprParse(info.text,(void*)(&info));

  //result
  if(info.result && info.retcode==MTCL_OK && !info.opStk) {
    mtclSetResult(i,info.result);
  } else if(info.opStk) {
    info.retcode=MTCL_ERR;
    mtclSetResult(info.i,"expr, not enough args for operation");
  }

  //cleanup
  while(mtclExprPopOp(&info));
  free(info.curWord);
  free(info.result);
  free(info.text);

  //
  return info.retcode;
}
