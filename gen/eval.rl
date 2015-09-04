 %%{

machine parse;

action parenStart {
  prnStart = fpc;
}

action cmntStart {
  DEBUG_MARK("comment:a",fpc);
}

action cmntEnd {
  DEBUG_MARK("comment:b",fpc);
}

action stmtStart {
  DEBUG_MARK("stmt:a",fpc);

  mStart=fpc;
  mEnd=fpc;
}

action stmtEnd {
  DEBUG_MARK("stmt:b",fpc);

  if(!mtclEvalParseStmtEndCallback(extraData)) {  //EVAL_WORDS
    runErr=true;
    fbreak;
  }
}

action wordStart { 
  DEBUG_MARK("- word:a",fpc);

  mStart=fpc;
  mEnd=fpc;
}

action wordEnd {
  DEBUG_MARK("- word:b",fpc);
  DEBUG_VAL("===========w",mStart,mEnd);

  if(mStart<mEnd) { //APPEND_WORD
    char *x=(char*)malloc(mEnd-mStart+1);
	sprintf(x,"%.*s",mEnd-mStart,mStart);
    bool r=mtclEvalParseStrCallback(extraData,mStart,mEnd,x);
    free(x);
	
    if(!r) {
      fbreak;
    }
  }
  
  if(!mtclEvalParseWordEndCallback(extraData)) { //APPEND_WORDS
    fbreak;
  } 
}

action subStart {
  DEBUG_MARK("- - sub:a",fpc);
}

action subEnd {
  DEBUG_MARK("- - sub:b",fpc);

  mStart=fpc;
  mEnd=fpc;
}

action varStart {
  DEBUG_MARK("- - - var:a",fpc);

  wStart=fpc;  
}

action varEnd {
  DEBUG_VAL("===========v",mStart,mEnd);

  if(mStart<mEnd) { //APPEND_WORD
    char *x=(char*)malloc(mEnd-mStart+1);
	sprintf(x,"%.*s",mEnd-mStart,mStart);
    bool r=mtclEvalParseStrCallback(extraData,mStart,mEnd,x);
    free(x);
	
    if(!r) {
      fbreak;
    }
  }
  
  const char *a=wStart+1;
  const char *b=fpc;
  
  if(a[0]=='{') {
    a++;
	b--;
  }

  DEBUG_MARK("- - - var:b",fpc);
  DEBUG_VAL("==========vv",a,b);

  {
    char *x=(char*)malloc(6+b-a+1);
	sprintf(x,"set {%.*s}",b-a,a);
    bool r=mtclEvalParseCmdCallback(extraData,a,b,x);
    free(x);
	
    if(!r) { //APPEND_WORD_CMD
      runErr=true;
      fbreak;
    }
  }
  
  wStart=fpc;
}

action cmdStart {
  DEBUG_MARK("- - - cmd:a",fpc);

  wStart=fpc;  
}

action cmdEnd {
  const char *a=wStart+1;
  const char *b=fpc-1;
  
  DEBUG_VAL("===========c",mStart,mEnd);
  DEBUG_MARK("- - - cmd:b",fpc);
  DEBUG_VAL("==========cc",a,b);

  if(mStart<mEnd) { //APPEND_WORD
    char *x=(char*)malloc(mEnd-mStart+1);
	sprintf(x,"%.*s",mEnd-mStart,mStart);
    bool r=mtclEvalParseStrCallback(extraData,mStart,mEnd,x);
    free(x);
	
    if(!r) {
      fbreak;
    }
  }
  {
    char *x=(char*)malloc(b-a+1);
	sprintf(x,"%.*s",b-a,a);
    bool r=mtclEvalParseCmdCallback(extraData,a,b,x);
    free(x);
	
    if(!r) { //APPEND_WORD_CMD
      runErr=true;
      fbreak;
    }
  }
  
  wStart=fpc;
}

action quoteStart {
  DEBUG_MARK("- - - qstr:a",fpc);

  wStart=fpc;
  mStart=fpc+1;  
}

action quoteEnd {
  DEBUG_MARK("- - - qstr:b",fpc);

  wStart=fpc;
}


action braceStart {
  DEBUG_MARK("- - - bstr:a",fpc);

  wStart=fpc;
}

action braceEnd {
  const char *a=wStart+1;
  const char *b=fpc-1;
  
  DEBUG_MARK("- - - bstr:b",fpc);
  DEBUG_VAL("==========bb",a,b);

  // if(!mtclEvalParseStrCallback(extraData,a,b)) { //APPEND_WORD
  //   fbreak;
  // }
  
    char *x=(char*)malloc(b-a+1);
	sprintf(x,"%.*s",b-a,a);
    bool r=mtclEvalParseStrCallback(extraData,a,b,x);
    free(x);
	
    if(!r) {
      fbreak;
    }
	
  wStart=fpc;
  mStart=fpc;
}

action charEnd {  
  DEBUG_MARK("- - - str_char:b",fpc);

  wStart=fpc; //what was this for?
  mEnd=fpc;
}

action qcharEnd {  
  DEBUG_MARK("- - - str_qchar:b",fpc);

  wStart=fpc;
  mEnd=fpc;
}

action quoteParenEof {
  quoteParenErr=true;
}

m_clybrace  := ([^{}] | ('{' @{fcall m_clybrace;}))* ('}' @{fret;});
m_sqrbrack := ([^\[\]] | ('[' @{fcall m_sqrbrack;}))* (']' @{fret;});
  
clybrace  = '{' >parenStart @{fcall m_clybrace;};
sqrbrack = '[' >parenStart @{fcall m_sqrbrack;};
  
spc         = [ \t\r];
not_spc_sep = [^ \t\r\n;];
eol         = '\n';
not_eol     = (any*)-(any* eol any*);
idn         = [_a-zA-Z0-9];
sep         = (eol | ';' ) spc*;

var = ('$' (idn+ | clybrace)) >varStart %varEnd ;
cmd = sqrbrack >cmdStart %cmdEnd ;
sub = (cmd|var) @(gchar,1) >subStart %subEnd ;
 
qchar = (sub |  [^\"] >(gchar,0) @(gchar,0) %qcharEnd );
schar = (not_spc_sep >(gchar,0)  %charEnd );

qstr = ('"' >parenStart >quoteStart qchar** $eof(quoteParenEof) '"'  ) $(gword,1) %quoteEnd ; 
str  = ( sub | schar )+ $(gword,0) ;
bstr = clybrace @(gword,1) >braceStart %braceEnd ;

word = (bstr|qstr|str) >wordStart %wordEnd ;
stmt = (word >stmtStart (spc+ word?)* %stmtEnd)  >(gstmt,0);
cmnt = ('#' >cmntStart not_eol %cmntEnd) $(gstmt,1) ; 

main := spc* sep* ((cmnt (eol space*)+) | (stmt sep+))* ((cmnt|stmt) sep*)?;
  
}%%

  

%% access fsm.;  
%% variable p fsm.p;
%% variable pe fsm.pe;
%% variable eof fsm.eof;

%%{

prepush {
}

postpop {
}

}%%


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef __cplusplus
#include <stdbool.h>
#endif

#ifdef MTCL_EVAL_PARSE_TEST
#define mtclEvalParseStrCallback(DATA,A,B,X) 1
#define mtclEvalParseCmdCallback(DATA,A,B,X) 1
#define mtclEvalParseWordEndCallback(DATA) 1
#define mtclEvalParseStmtEndCallback(DATA) 1
#define mtclEvalParseParenErrCallback(D,P)
#define mtclEvalParseErrCallback(D,P)
#define mtclEvalParseRunErrCallback(D,P)

#define MTCL_EVAL_PARSE_DEBUG
#else
#include "mtclEvalParse.h"
#endif

#ifndef MTCL_EVAL_PARSE_DEBUG
#define DEBUG_MARK(X,P)
#define DEBUG_VAL(X,A,B) 
#else
#define DEBUG_MARK(X,P) \
  printf("%s %i\n",X,(int)(P-text));
  
#define DEBUG_VAL(X,A,B) \
  if(A<B) { \
    printf("%s '%.*s'\n",X,(int)(B-A),A); \
  } else if(0) { \
    printf("%s (%i %i)\n",X,(int)(A-text),(int)(B-text)); \
  }

#endif

void mtclEvalParse(const char *text,void *extraData) {
  %% write data;
  
  struct {
    int cs;
    const char *p,*pe,*eof;
    int stack[128],top;
  } fsm;
  
  %% write init;
  
  fsm.p=text;
  fsm.pe=text+strlen(text);
  fsm.eof=fsm.pe;
    
  const char *prnStart=0;
  const char *wStart=0;
  const char *mStart=0,*mEnd=0;
  bool runErr=false;
  bool done=false;
  bool quoteParenErr=false;
  
  %% write exec;
  if(runErr) {
    mtclEvalParseRunErrCallback(extraData,fsm.p);
  } else if(fsm.top != 0 || quoteParenErr) {
    DEBUG_MARK("paren err",fsm.p);
    mtclEvalParseParenErrCallback(extraData,prnStart);
  } else if(fsm.cs < %%{ write first_final; }%%) {
    DEBUG_MARK("err",fsm.p);
    mtclEvalParseErrCallback(extraData,fsm.p);
  } 
}

#ifdef MTCL_EVAL_PARSE_TEST
char *stringFromFile(const char *fn) {
  FILE *file = fopen(fn, "rb");
  if(!file) { return 0;  }
  fseek(file,0L,SEEK_END);
  unsigned int dataSize = ftell(file);
  fseek(file,0L,SEEK_SET);
  char *str=(char*)malloc(dataSize+1);
  str[dataSize]='\0';//is not already null terminated?
  fread(str,1,dataSize,file);
  fclose(file);
  return str;
}

int main() {
  char *text=stringFromFile("tests/evaltest.tcl");
  mtclEvalParse(text,0);
  free(text);
  printf("done\n");
  return 0;
}
#endif