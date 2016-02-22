 %%{

machine exprParse;

action parenStart {
  prnStart = fpc;
}

action wordStart { 
  DEBUG_MARK("- word:a",fpc);

  mStart=fpc;
  mEnd=fpc;
}

action wordEnd {
  DEBUG_MARK("- word:b",fpc);
  DEBUG_VAL("===========w",mStart,mEnd);

  if(!isMath) {
    if(mStart<mEnd) { //APPEND_WORD
      char *x=(char*)malloc(mEnd-mStart+1);
	  sprintf(x,"%.*s",mEnd-mStart,mStart);
	  bool r=mtclExprParseStrCallback(extraData,mStart,mEnd,x);
	  free(x);
	  
      if(!r) {
        fbreak;
      }
    }
  
    if(!mtclExprParseWordEndCallback(extraData)) { //APPEND_WORDS
      fbreak;
    }
  }
  
  isMath=false;
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
	bool r=mtclExprParseStrCallback(extraData,mStart,mEnd,x);
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
    bool r=mtclExprParseCmdCallback(extraData,a,b,x);
    free(x);
	
    if(!r) { //APPEND_WORD_VAR
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
	bool r=mtclExprParseStrCallback(extraData,mStart,mEnd,x);
	free(x);
	
    if(!r) {
      fbreak;
    }
  }
  
  {  
    char *x=(char*)malloc(b-a+1);
	sprintf(x,"%.*s",b-a,a);
	bool r=mtclExprParseCmdCallback(extraData,a,b,x);
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
  
  {
    char *x=(char*)malloc(b-a+1);
	sprintf(x,"%.*s",b-a,a);
	bool r=mtclExprParseStrCallback(extraData,a,b,x);
	free(x);
	
    if(!r) { //APPEND_WORD
      fbreak;
    }
  }

  wStart=fpc;
  mStart=fpc;
}

action charEnd {  
  DEBUG_MARK("- - - str_char:b",fpc);

  //wStart=fpc; //what was this for?
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

action mathStart {
  DEBUG_MARK("- - - math:a",fpc);
  wStart=fpc;
}

action mathEnd {
  DEBUG_MARK("- - - math:b",fpc);
  DEBUG_VAL("===========m",wStart,fpc);
  
  {
    const char *a=wStart;
	const char *b=fpc;
	
    char *x=(char*)malloc(b-a+1);
	sprintf(x,"%.*s",b-a,a);
	bool r=mtclExprParseMathEndCallback(extraData,a,b,x);
	free(x);
	
    if(!r) {
      fbreak;
    }
  }
  
  isMath=true;
  wStart=fpc;
  mStart=fpc;
}

m_clybrace  := ([^{}] | ('{' @{fcall m_clybrace;}))* ('}' @{fret;});
m_sqrbrack := ([^\[\]] | ('[' @{fcall m_sqrbrack;}))* (']' @{fret;});
  
clybrace = '{' >parenStart @{fcall m_clybrace;};
sqrbrack = '[' >parenStart @{fcall m_sqrbrack;};
  
spc         = [ \t\r\n];
not_spc_sep = [^ \t\r\n;];
idn         = [_a-zA-Z0-9];

var = ('$' (idn+ | clybrace)) >varStart %varEnd;
cmd = sqrbrack >cmdStart %cmdEnd;
sub = (cmd|var) $(gchar,1) >subStart %subEnd;
 
qchar = (sub |  [^\"] $(gchar,0) %qcharEnd);
schar = (not_spc_sep $(gchar,0) %charEnd );

qstr = ('"' >parenStart >quoteStart qchar** $eof(quoteParenEof) '"') >(gword,1) @(gword,1) %quoteEnd; 
str  = ( sub | schar )+ >(gword,0);
bstr = clybrace >(gword,1) @(gword,1) >braceStart %braceEnd;

math1 =('-' | '+' | '~' | '!' | '*' | '/' |
        '%' | '<' | '>' | '&' | '^' | '|' |
        '?')  @(gword,2) >mathStart %mathEnd;
		
math2 =('**' | '<<' | '>>' | '<=' | '>=' | 
        '==' | '!=' | '||' | '&&' |
        '//')  @(gword,3) >mathStart %mathEnd;
		
mathf =('eq' | 'ne' | 'in' | 'ni' | 'neg' |
        'abs' | 'acos' | 'asin' | 'atan' |
        'atan2' | 'bool' | 'ceil' | 'cos' |
        'cosh' | 'double' | 'entier' | 'exp' |
        'floor' | 'fmod' | 'hypot' | 'int' | 
        'isqrt' | 'log' | 'log10' | 'max' |
        'min' | 'pow' | 'rand' | 'round' | 
        'sin' | 'sinh' | 'sqrt' | 'srand' | 
        'tan' | 'tanh' |
        'wide') @(gword,4) >mathStart %mathEnd;
		
word = (mathf|math2|math1|bstr|qstr|str) >wordStart %wordEnd;

main := spc* (word (spc+ word?)* spc*)?;
  
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

#ifdef MTCL_EXPR_PARSE_TEST
#define mtclExprParseStrCallback(DATA,A,B,X) 1
#define mtclExprParseCmdCallback(DATA,A,B,X) 1
#define mtclExprParseWordEndCallback(DATA) 1
#define mtclExprParseMathEndCallback(DATA,A,B,X) 1
#define mtclExprParseParenErrCallback(D,P)
#define mtclExprParseErrCallback(D,P)
#define mtclExprParseRunErrCallback(D,P)
	
#define MTCL_EXPR_PARSE_DEBUG
#else
#include "mtclExprParse.h"
#endif

#ifndef MTCL_EXPR_PARSE_DEBUG
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

bool mtclExprParse(const char *text,void *extraData) {
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
  bool isMath=false;
  
  %% write exec;

  if(runErr) {
    mtclExprParseRunErrCallback(extraData,fsm.p);
	return false;
  } else if(fsm.top != 0 || quoteParenErr) {
    DEBUG_MARK("paren err",fsm.p);
    mtclExprParseParenErrCallback(extraData,prnStart);
	return false;
  } else if(fsm.cs < %%{ write first_final; }%%) {
    DEBUG_MARK("err",fsm.p);
    mtclExprParseErrCallback(extraData,fsm.p);
	return false;
  } 
  
  return true;
}

#ifdef MTCL_EXPR_PARSE_TEST
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
  char *text=stringFromFile("tests/exprtest.txt");
  mtclExprParse(text,0);
  free(text);
  printf("done\n");
  return 0;
}
#endif