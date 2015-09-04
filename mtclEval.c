#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#ifdef _MSC_VER
#define snprintf _snprintf
#endif

#include "mtclEvalParse.h"
#include "mtclEval.h"

struct mtclEvalInfo {
  struct mtclInterp *i;
  char *text;
  char *curWord;
  char **words;
  int wordsNum,wordsMaxNum;
  char errbuf[1024];
  int retcode;
};

void mtclEvalAppendCurWord(struct mtclEvalInfo *info,const char *x) {
  size_t m=strlen(x);
  size_t n=info->curWord?strlen(info->curWord):0;
  info->curWord=(char*)realloc(info->curWord,n+m+1);
  memcpy(&info->curWord[n],x,m);
  info->curWord[n+m]='\0';
}

bool mtclEvalParseStrCallback(void *data,const char *a,const char *b,
                               const char *x) {
  //on receiving part of a word
#ifdef MTCL_EVAL_DEBUG
  printf("%.*s",(int)(b-a),a);
#else
  struct mtclEvalInfo *info;
  info=(struct mtclEvalInfo*)data;

  mtclEvalAppendCurWord(info,x);
  info->retcode=MTCL_OK; //probably not necessary
#endif

  return true;
}


bool mtclEvalParseCmdCallback(void *data,const char *a,const char *b,
                              const char *x) {
  //on receiving a cmd part of a word
#ifdef MTCL_EVAL_DEBUG
  printf("[%.*s]",(int)(b-a),a);
#else
  struct mtclEvalInfo *info;
  info=(struct mtclEvalInfo*)data;
  info->retcode=mtclEval(info->i,x);

  //on return/break/continue status it must stop evaluating
  if(info->retcode != MTCL_OK) {
    return false;
  }

  mtclEvalAppendCurWord(info,info->i->result);
#endif

  return true;
}

bool mtclEvalParseWordEndCallback(void *data) {
  //on end of word
#ifdef MTCL_EVAL_DEBUG
  printf("\n");
#else
  struct mtclEvalInfo *info;
  info=(struct mtclEvalInfo*)data;

  if(info->wordsNum >= info->wordsMaxNum) {
    info->words=(char**)realloc(info->words,
                                sizeof(void*)*(++info->wordsMaxNum));
  }

  info->words[info->wordsNum++]=info->curWord;
  info->curWord=0;
#endif

  return true;
}

bool mtclEvalParseStmtEndCallback(void *data) {
  //on end of stmt
#ifdef MTCL_EVAL_DEBUG
  printf(";\n");
#else
  struct mtclEvalInfo *info;
  info=(struct mtclEvalInfo*)data;
  int j;
  struct mtclCmd *c;

  c=mtclGetCommand(info->i,info->words[0]);

  if(!c) {
    snprintf(info->errbuf,1024,"No such command '%s'",info->words[0]);
    mtclSetResult(info->i,info->errbuf);
    info->retcode=MTCL_ERR;
    return false;
  }

  mtclSetResult(info->i,"");
  info->retcode = c->func(info->i,info->wordsNum,info->words,c->privdata);

  if(info->retcode != MTCL_OK) {
    return false;
  }


  for(j=0;j<info->wordsNum;j++) {
    free(info->words[j]);
  }

  info->wordsNum=0;
#endif

  return true;
}

void mtclEvalParseErr(const char *lbl,struct mtclEvalInfo *info,const char *p) {
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

void mtclEvalParseErrCallback(void *data,const char *p) {
  struct mtclEvalInfo *info;
  info=(struct mtclEvalInfo*)data;

  mtclEvalParseErr("parse error",info,p);
}

void mtclEvalParseParenErrCallback(void *data,const char *p) {
  struct mtclEvalInfo *info;
  info=(struct mtclEvalInfo*)data;

  mtclEvalParseErr("no matching paren error",info,p);
}

void mtclEvalParseRunErrCallback(void *data,const char *p) {
  struct mtclEvalInfo *info;
  info=(struct mtclEvalInfo*)data;

  // mtclEvalParseErr("runerr",info,p);
  //todo
}

int mtclEval(struct mtclInterp *i,const char *text) {
  struct mtclEvalInfo info;
  info.i=i;
  info.text=strdup(text);
  info.curWord=0;
  info.words=0;
  info.wordsNum=0;
  info.wordsMaxNum=0;
  info.retcode=MTCL_OK;

  //
  mtclEvalParse(info.text,(void*)(&info));

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
