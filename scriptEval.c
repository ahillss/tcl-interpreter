#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#ifdef _MSC_VER
#define snprintf _snprintf
#endif

#include "scriptEvalParse.h"
#include "scriptEval.h"

struct scriptEvalInfo {
  struct scriptInterp *i;
  char *text;
  char *curWord;
  char **words;
  int wordsNum,wordsMaxNum;
  char errbuf[1024];
  int retcode;
};

void scriptEvalAppendCurWord(struct scriptEvalInfo *info,
                            const char *a,const char *b) {
  size_t m=(b-a);
  size_t n=info->curWord?strlen(info->curWord):0;
  info->curWord=(char*)realloc(info->curWord,n+m+1);
  memcpy(&info->curWord[n],a,m);
  info->curWord[n+m]='\0';
}

bool scriptEvalParsePartCallback(void *data,const char *a,const char *b) {
  //on receiving part of a word
#ifdef SCRIPT_EVAL_DEBUG
  printf("%.*s",(int)(b-a),a);
#else
  struct scriptEvalInfo *info;
  info=(struct scriptEvalInfo*)data;

  scriptEvalAppendCurWord(info,a,b);
  info->retcode=SCRIPT_OK; //probably not necessary
#endif

  return true;
}

bool scriptEvalParseVarCallback(void *data,const char *a,const char *b) {
  //on receiving a var part of a word
#ifdef SCRIPT_EVAL_DEBUG
  printf("${%.*s}",(int)(b-a),a);
#else
  struct scriptEvalInfo *info;
  info=(struct scriptEvalInfo*)data;

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

  scriptEvalAppendCurWord(info,pv->val,pv->val+strlen(pv->val));
  free(tmp);
  info->retcode=SCRIPT_OK; //probably not necessary
#endif

  return true;
}

bool scriptEvalParseCmdCallback(void *data,const char *a,const char *b) {
  //on receiving a cmd part of a word
#ifdef SCRIPT_EVAL_DEBUG
  printf("[%.*s]",(int)(b-a),a);
#else
  struct scriptEvalInfo *info;
  info=(struct scriptEvalInfo*)data;

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

  scriptEvalAppendCurWord(info,info->i->result,
                         info->i->result+strlen(info->i->result));
#endif

  return true;
}

bool scriptEvalParseWordEndCallback(void *data) {
  //on end of word
#ifdef SCRIPT_EVAL_DEBUG
  printf("\n");
#else
  struct scriptEvalInfo *info;
  info=(struct scriptEvalInfo*)data;

  if(info->wordsNum >= info->wordsMaxNum) {
    info->words=(char**)realloc(info->words,
                                sizeof(void*)*(++info->wordsMaxNum));
  }

  info->words[info->wordsNum++]=info->curWord;
  info->curWord=0;
#endif

  return true;
}

bool scriptEvalParseStmtEndCallback(void *data) {
  //on end of stmt
#ifdef SCRIPT_EVAL_DEBUG
  printf(";\n");
#else
  struct scriptEvalInfo *info;
  info=(struct scriptEvalInfo*)data;
  int j;
  struct scriptCmd *c;

  c=scriptGetCommand(info->i,info->words[0]);

  if(!c) {
    snprintf(info->errbuf,1024,"No such command '%s'",info->words[0]);
    scriptSetResult(info->i,info->errbuf);
    info->retcode=SCRIPT_ERR;
    return false;
  }

  scriptSetResult(info->i,"");
  info->retcode = c->func(info->i,info->wordsNum,info->words,c->privdata);

  if(info->retcode != SCRIPT_OK) {
    return false;
  }


  for(j=0;j<info->wordsNum;j++) {
    free(info->words[j]);
  }

  info->wordsNum=0;
#endif

  return true;
}

void scriptEvalParseErr(const char *lbl,struct scriptEvalInfo *info,const char *p) {
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

void scriptEvalParseErrCallback(void *data,const char *p) {
  struct scriptEvalInfo *info;
  info=(struct scriptEvalInfo*)data;

  scriptEvalParseErr("parse error",info,p);
}

void scriptEvalParseParenErrCallback(void *data,const char *p) {
  struct scriptEvalInfo *info;
  info=(struct scriptEvalInfo*)data;

  scriptEvalParseErr("no matching paren error",info,p);
}

void scriptEvalParseRunErrCallback(void *data,const char *p) {
  struct scriptEvalInfo *info;
  info=(struct scriptEvalInfo*)data;

  // scriptEvalParseErr("runerr",info,p);
  //todo
}

int scriptEval(struct scriptInterp *i,const char *text) {
  struct scriptEvalInfo info;
  info.i=i;
  info.text=strdup(text);
  info.curWord=0;
  info.words=0;
  info.wordsNum=0;
  info.wordsMaxNum=0;
  info.retcode=SCRIPT_OK;

  //
  scriptEvalParse(info.text,(void*)(&info));

  //
  int j;

  for(j=0;j<info.wordsNum;j++) {
    free(info.words[j]);
  }

  free(info.words);
  free(info.curWord);
  free(info.text);

  //
  return info.retcode;
}
