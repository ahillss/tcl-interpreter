
#line 1 "expr.rl"
 
#line 223 "expr.rl"



#line 226 "expr.rl"

#line 227 "expr.rl"

#line 228 "expr.rl"

#line 229 "expr.rl"


#line 238 "expr.rl"


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef __cplusplus
#include <stdbool.h>
#endif

#ifdef SCRIPT_EXPR_PARSE_TEST
#define scriptExprParsePartCallback(DATA,A,B) 1
#define scriptExprParseVarCallback(DATA,A,B) 1
#define scriptExprParseCmdCallback(DATA,A,B) 1
#define scriptExprParseWordEndCallback(DATA) 1
#define scriptExprParseMathEndCallback(DATA,A,B) 1
#define scriptExprParseParenErrCallback(D,P)
#define scriptExprParseErrCallback(D,P)
#define scriptExprParseRunErrCallback(D,P)
	
#define SCRIPT_EXPR_PARSE_DEBUG
#else
#include "scriptExprParse.h"
#endif

#ifndef SCRIPT_EXPR_PARSE_DEBUG
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

bool scriptExprParse(const char *text,void *extraData) {
  
#line 62 "tmp/scriptExprParse.c"
static const char _exprParse_actions[] = {
	0, 1, 1, 1, 13, 1, 14, 1, 
	15, 1, 18, 1, 19, 1, 20, 1, 
	21, 2, 0, 22, 2, 1, 16, 2, 
	3, 5, 2, 6, 4, 2, 8, 4, 
	2, 10, 2, 2, 12, 2, 2, 13, 
	2, 2, 17, 2, 3, 1, 0, 9, 
	3, 1, 3, 5, 3, 6, 4, 2, 
	3, 8, 4, 2, 3, 13, 3, 5, 
	3, 14, 3, 5, 3, 17, 13, 2, 
	4, 1, 11, 0, 22, 4, 3, 7, 
	0, 23, 4, 6, 4, 3, 5, 4, 
	8, 4, 3, 5, 5, 1, 3, 7, 
	0, 23, 5, 13, 3, 7, 0, 23, 
	5, 14, 3, 7, 0, 23, 6, 6, 
	4, 3, 7, 0, 23, 6, 8, 4, 
	3, 7, 0, 23
};

static const short _exprParse_key_offsets[] = {
	0, 0, 8, 11, 14, 22, 32, 35, 
	38, 42, 43, 44, 45, 46, 47, 48, 
	49, 50, 51, 53, 54, 55, 56, 57, 
	58, 59, 60, 63, 64, 65, 66, 67, 
	68, 70, 71, 72, 73, 74, 75, 76, 
	77, 78, 80, 81, 82, 83, 84, 85, 
	87, 88, 90, 91, 92, 94, 95, 96, 
	99, 100, 101, 102, 103, 104, 106, 108, 
	147, 154, 168, 175, 182, 190, 197, 201, 
	209, 217, 225, 234, 242, 251, 255, 260, 
	265, 270, 275, 280, 284, 292, 292
};

static const char _exprParse_trans_keys[] = {
	95, 123, 48, 57, 65, 90, 97, 122, 
	34, 36, 91, 34, 36, 91, 95, 123, 
	48, 57, 65, 90, 97, 122, 34, 36, 
	91, 95, 48, 57, 65, 90, 97, 122, 
	34, 36, 91, 34, 36, 91, 98, 99, 
	115, 116, 115, 111, 105, 110, 97, 110, 
	111, 111, 108, 101, 111, 105, 115, 111, 
	117, 98, 108, 101, 110, 113, 120, 116, 
	105, 101, 114, 112, 108, 109, 111, 111, 
	111, 100, 121, 112, 111, 116, 110, 115, 
	113, 114, 111, 103, 48, 97, 105, 120, 
	101, 105, 111, 119, 97, 111, 110, 117, 
	105, 113, 114, 110, 97, 97, 105, 100, 
	123, 125, 91, 93, 13, 32, 33, 34, 
	36, 37, 38, 42, 43, 45, 47, 59, 
	60, 61, 62, 63, 91, 94, 97, 98, 
	99, 100, 101, 102, 104, 105, 108, 109, 
	110, 112, 114, 115, 116, 119, 123, 124, 
	126, 9, 10, 13, 32, 36, 59, 91, 
	9, 10, 13, 32, 36, 59, 91, 95, 
	9, 10, 48, 57, 65, 90, 97, 122, 
	13, 32, 36, 59, 91, 9, 10, 13, 
	32, 36, 59, 91, 9, 10, 13, 32, 
	36, 59, 61, 91, 9, 10, 13, 32, 
	36, 59, 91, 9, 10, 13, 32, 9, 
	10, 13, 32, 36, 38, 59, 91, 9, 
	10, 13, 32, 36, 42, 59, 91, 9, 
	10, 13, 32, 36, 47, 59, 91, 9, 
	10, 13, 32, 36, 59, 91, 9, 10, 
	60, 61, 13, 32, 36, 59, 61, 91, 
	9, 10, 13, 32, 36, 59, 91, 9, 
	10, 61, 62, 13, 32, 9, 10, 13, 
	32, 50, 9, 10, 13, 32, 104, 9, 
	10, 13, 32, 116, 9, 10, 13, 32, 
	49, 9, 10, 13, 32, 103, 9, 10, 
	13, 32, 9, 10, 13, 32, 36, 59, 
	91, 124, 9, 10, 0
};

static const char _exprParse_single_lengths[] = {
	0, 2, 3, 3, 2, 4, 3, 3, 
	4, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 2, 1, 1, 1, 1, 1, 
	1, 1, 3, 1, 1, 1, 1, 1, 
	2, 1, 1, 1, 1, 1, 1, 1, 
	1, 2, 1, 1, 1, 1, 1, 2, 
	1, 2, 1, 1, 2, 1, 1, 3, 
	1, 1, 1, 1, 1, 2, 2, 37, 
	5, 6, 5, 5, 6, 5, 2, 6, 
	6, 6, 5, 6, 5, 2, 3, 3, 
	3, 3, 3, 2, 6, 0, 0
};

static const char _exprParse_range_lengths[] = {
	0, 3, 0, 0, 3, 3, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 1, 
	1, 4, 1, 1, 1, 1, 1, 1, 
	1, 1, 2, 1, 2, 1, 1, 1, 
	1, 1, 1, 1, 1, 0, 0
};

static const short _exprParse_index_offsets[] = {
	0, 0, 6, 10, 14, 20, 28, 32, 
	36, 41, 43, 45, 47, 49, 51, 53, 
	55, 57, 59, 62, 64, 66, 68, 70, 
	72, 74, 76, 80, 82, 84, 86, 88, 
	90, 93, 95, 97, 99, 101, 103, 105, 
	107, 109, 112, 114, 116, 118, 120, 122, 
	125, 127, 130, 132, 134, 137, 139, 141, 
	145, 147, 149, 151, 153, 155, 158, 161, 
	200, 207, 218, 225, 232, 240, 247, 251, 
	259, 267, 275, 283, 291, 299, 303, 308, 
	313, 318, 323, 328, 332, 340, 341
};

static const char _exprParse_indicies[] = {
	0, 2, 0, 0, 0, 1, 4, 5, 
	6, 3, 8, 9, 10, 7, 11, 12, 
	11, 11, 11, 1, 14, 15, 16, 11, 
	11, 11, 11, 13, 18, 19, 20, 17, 
	14, 15, 16, 13, 21, 22, 23, 24, 
	1, 25, 1, 21, 1, 26, 1, 25, 
	1, 27, 1, 28, 1, 29, 1, 30, 
	1, 25, 1, 31, 32, 1, 30, 1, 
	33, 1, 34, 1, 35, 1, 36, 1, 
	37, 1, 25, 1, 38, 25, 39, 1, 
	40, 1, 41, 1, 42, 1, 25, 1, 
	25, 1, 43, 44, 1, 45, 1, 42, 
	1, 46, 1, 25, 1, 47, 1, 48, 
	1, 49, 1, 25, 1, 50, 51, 1, 
	52, 1, 49, 1, 53, 1, 54, 1, 
	25, 1, 55, 26, 1, 25, 1, 56, 
	25, 1, 57, 1, 25, 1, 58, 59, 
	1, 46, 1, 58, 1, 60, 52, 61, 
	1, 33, 1, 58, 1, 60, 1, 62, 
	1, 37, 1, 64, 65, 63, 67, 68, 
	66, 70, 70, 71, 72, 73, 74, 75, 
	76, 74, 74, 77, 1, 78, 79, 80, 
	74, 81, 74, 82, 83, 84, 85, 86, 
	87, 88, 89, 90, 91, 92, 93, 94, 
	95, 96, 97, 98, 99, 74, 70, 69, 
	101, 101, 102, 1, 103, 101, 100, 105, 
	105, 106, 1, 107, 0, 105, 0, 0, 
	0, 104, 109, 109, 110, 1, 111, 109, 
	108, 105, 105, 106, 1, 107, 105, 104, 
	112, 112, 102, 1, 113, 103, 112, 100, 
	112, 112, 102, 1, 103, 112, 100, 114, 
	114, 114, 1, 112, 112, 102, 113, 1, 
	103, 112, 100, 112, 112, 102, 113, 1, 
	103, 112, 100, 112, 112, 102, 113, 1, 
	103, 112, 100, 112, 112, 102, 1, 103, 
	112, 113, 100, 101, 101, 102, 1, 113, 
	103, 101, 100, 112, 112, 102, 1, 103, 
	112, 113, 100, 115, 115, 115, 1, 115, 
	115, 25, 115, 1, 115, 115, 25, 115, 
	1, 115, 115, 25, 115, 1, 115, 115, 
	116, 115, 1, 115, 115, 25, 115, 1, 
	117, 117, 117, 1, 112, 112, 102, 1, 
	103, 113, 112, 100, 1, 1, 0
};

static const char _exprParse_trans_targs[] = {
	65, 0, 67, 3, 70, 4, 6, 3, 
	70, 4, 6, 5, 7, 3, 70, 4, 
	6, 3, 70, 4, 6, 9, 10, 11, 
	13, 77, 12, 14, 78, 16, 17, 19, 
	20, 79, 22, 23, 24, 25, 27, 31, 
	28, 29, 30, 33, 35, 34, 36, 38, 
	39, 40, 80, 42, 43, 45, 81, 48, 
	82, 51, 53, 54, 56, 57, 60, 61, 
	61, 85, 62, 62, 86, 64, 63, 68, 
	2, 1, 69, 71, 72, 73, 74, 75, 
	76, 66, 8, 15, 18, 21, 26, 32, 
	37, 41, 44, 47, 49, 50, 52, 55, 
	58, 59, 83, 84, 64, 63, 1, 66, 
	64, 63, 1, 66, 64, 63, 1, 66, 
	63, 69, 63, 63, 46, 63
};

static const char _exprParse_trans_actions[] = {
	0, 0, 17, 0, 0, 23, 77, 5, 
	5, 64, 104, 0, 17, 26, 26, 82, 
	110, 29, 29, 87, 117, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	9, 11, 0, 13, 15, 1, 0, 20, 
	44, 48, 20, 20, 20, 20, 20, 20, 
	20, 92, 20, 20, 20, 20, 20, 20, 
	20, 20, 20, 20, 20, 20, 20, 20, 
	20, 20, 72, 20, 3, 38, 60, 98, 
	26, 52, 82, 110, 29, 56, 87, 117, 
	68, 3, 32, 41, 0, 35
};

static const char _exprParse_eof_actions[] = {
	0, 0, 7, 7, 7, 7, 7, 7, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	38, 52, 56, 52, 68, 68, 32, 68, 
	68, 68, 68, 38, 68, 41, 41, 41, 
	41, 41, 41, 35, 68, 0, 0
};

static const int exprParse_start = 63;
static const int exprParse_first_final = 63;
static const int exprParse_error = 0;

static const int exprParse_en_m_clybrace = 61;
static const int exprParse_en_m_sqrbrack = 62;
static const int exprParse_en_main = 63;


#line 281 "expr.rl"
  
  struct {
    int cs;
    const char *p,*pe,*eof;
    int stack[128],top;
  } fsm;
  
  
#line 292 "tmp/scriptExprParse.c"
	{
	 fsm.cs = exprParse_start;
	 fsm.top = 0;
	}

#line 289 "expr.rl"
  
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
  
  
#line 313 "tmp/scriptExprParse.c"
	{
	int _klen;
	unsigned int _trans;
	const char *_acts;
	unsigned int _nacts;
	const char *_keys;

	if ( ( fsm.p) == ( fsm.pe) )
		goto _test_eof;
	if (  fsm.cs == 0 )
		goto _out;
_resume:
	_keys = _exprParse_trans_keys + _exprParse_key_offsets[ fsm.cs];
	_trans = _exprParse_index_offsets[ fsm.cs];

	_klen = _exprParse_single_lengths[ fsm.cs];
	if ( _klen > 0 ) {
		const char *_lower = _keys;
		const char *_mid;
		const char *_upper = _keys + _klen - 1;
		while (1) {
			if ( _upper < _lower )
				break;

			_mid = _lower + ((_upper-_lower) >> 1);
			if ( (*( fsm.p)) < *_mid )
				_upper = _mid - 1;
			else if ( (*( fsm.p)) > *_mid )
				_lower = _mid + 1;
			else {
				_trans += (unsigned int)(_mid - _keys);
				goto _match;
			}
		}
		_keys += _klen;
		_trans += _klen;
	}

	_klen = _exprParse_range_lengths[ fsm.cs];
	if ( _klen > 0 ) {
		const char *_lower = _keys;
		const char *_mid;
		const char *_upper = _keys + (_klen<<1) - 2;
		while (1) {
			if ( _upper < _lower )
				break;

			_mid = _lower + (((_upper-_lower) >> 1) & ~1);
			if ( (*( fsm.p)) < _mid[0] )
				_upper = _mid - 2;
			else if ( (*( fsm.p)) > _mid[1] )
				_lower = _mid + 2;
			else {
				_trans += (unsigned int)((_mid - _keys)>>1);
				goto _match;
			}
		}
		_trans += _klen;
	}

_match:
	_trans = _exprParse_indicies[_trans];
	 fsm.cs = _exprParse_trans_targs[_trans];

	if ( _exprParse_trans_actions[_trans] == 0 )
		goto _again;

	_acts = _exprParse_actions + _exprParse_trans_actions[_trans];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 )
	{
		switch ( *_acts++ )
		{
	case 0:
#line 5 "expr.rl"
	{
  prnStart = ( fsm.p);
}
	break;
	case 1:
#line 9 "expr.rl"
	{ 
  DEBUG_MARK("- word:a",( fsm.p));

  mStart=( fsm.p);
  mEnd=( fsm.p);
}
	break;
	case 2:
#line 16 "expr.rl"
	{
  DEBUG_MARK("- word:b",( fsm.p));
  DEBUG_VAL("===========w",mStart,mEnd);

  if(!isMath) {
  if(mStart<mEnd) { //APPEND_WORD
    if(!scriptExprParsePartCallback(extraData,mStart,mEnd)) {
      {( fsm.p)++; goto _out; }
    }
  }
  
  if(!scriptExprParseWordEndCallback(extraData)) { //APPEND_WORDS
    {( fsm.p)++; goto _out; }
  }
  }
  
  isMath=false;
}
	break;
	case 3:
#line 35 "expr.rl"
	{
  DEBUG_MARK("- - sub:a",( fsm.p));
}
	break;
	case 4:
#line 39 "expr.rl"
	{
  DEBUG_MARK("- - sub:b",( fsm.p));

  mStart=( fsm.p);
  mEnd=( fsm.p);
}
	break;
	case 5:
#line 46 "expr.rl"
	{
  DEBUG_MARK("- - - var:a",( fsm.p));

  wStart=( fsm.p);  
}
	break;
	case 6:
#line 52 "expr.rl"
	{
  DEBUG_VAL("===========v",mStart,mEnd);

  if(mStart<mEnd) { //APPEND_WORD
    if(!scriptExprParsePartCallback(extraData,mStart,mEnd)) {
      {( fsm.p)++; goto _out; }
    }
  }
  
  const char *a=wStart+1;
  const char *b=( fsm.p);
  
  if(a[0]=='{') {
    a++;
	b--;
  }

  DEBUG_MARK("- - - var:b",( fsm.p));
  DEBUG_VAL("==========vv",a,b);

  if(!scriptExprParseVarCallback(extraData,a,b)) { //APPEND_WORD_VAR
    runErr=true;
    {( fsm.p)++; goto _out; }
  }

  wStart=( fsm.p);
}
	break;
	case 7:
#line 80 "expr.rl"
	{
  DEBUG_MARK("- - - cmd:a",( fsm.p));

  wStart=( fsm.p);  
}
	break;
	case 8:
#line 86 "expr.rl"
	{
  const char *a=wStart+1;
  const char *b=( fsm.p)-1;
  
  DEBUG_VAL("===========c",mStart,mEnd);
  DEBUG_MARK("- - - cmd:b",( fsm.p));
  DEBUG_VAL("==========cc",a,b);

  if(mStart<mEnd) { //APPEND_WORD
    if(!scriptExprParsePartCallback(extraData,mStart,mEnd)) {
      {( fsm.p)++; goto _out; }
    }
  }
   
  if(!scriptExprParseCmdCallback(extraData,a,b)) { //APPEND_WORD_CMD
    runErr=true;
    {( fsm.p)++; goto _out; }
  }
  
  wStart=( fsm.p);
}
	break;
	case 9:
#line 108 "expr.rl"
	{
  DEBUG_MARK("- - - qstr:a",( fsm.p));

  wStart=( fsm.p);
  mStart=( fsm.p)+1;  
}
	break;
	case 10:
#line 115 "expr.rl"
	{
  DEBUG_MARK("- - - qstr:b",( fsm.p));

  wStart=( fsm.p);
}
	break;
	case 11:
#line 122 "expr.rl"
	{
  DEBUG_MARK("- - - bstr:a",( fsm.p));

  wStart=( fsm.p);
}
	break;
	case 12:
#line 128 "expr.rl"
	{
  const char *a=wStart+1;
  const char *b=( fsm.p)-1;
  
  DEBUG_MARK("- - - bstr:b",( fsm.p));
  DEBUG_VAL("==========bb",a,b);

  if(!scriptExprParsePartCallback(extraData,a,b)) { //APPEND_WORD
    {( fsm.p)++; goto _out; }
  }

  wStart=( fsm.p);
  mStart=( fsm.p);
}
	break;
	case 13:
#line 143 "expr.rl"
	{  
  DEBUG_MARK("- - - str_char:b",( fsm.p));

  wStart=( fsm.p);
  mEnd=( fsm.p);
}
	break;
	case 14:
#line 150 "expr.rl"
	{  
  DEBUG_MARK("- - - str_qchar:b",( fsm.p));

  wStart=( fsm.p);
  mEnd=( fsm.p);
}
	break;
	case 16:
#line 161 "expr.rl"
	{
  DEBUG_MARK("- - - math:a",( fsm.p));
  wStart=( fsm.p);
}
	break;
	case 17:
#line 166 "expr.rl"
	{
  DEBUG_MARK("- - - math:b",( fsm.p));
  DEBUG_VAL("===========m",wStart,( fsm.p));
  
  if(!scriptExprParseMathEndCallback(extraData,wStart,( fsm.p))) {
    {( fsm.p)++; goto _out; }
  }
  
  isMath=true;
  wStart=( fsm.p);
  mStart=( fsm.p);
}
	break;
	case 18:
#line 179 "expr.rl"
	{{
{ fsm.stack[ fsm.top++] =  fsm.cs;  fsm.cs = 61; goto _again;}}}
	break;
	case 19:
#line 179 "expr.rl"
	{{ fsm.cs =  fsm.stack[-- fsm.top]; {
}goto _again;}}
	break;
	case 20:
#line 180 "expr.rl"
	{{
{ fsm.stack[ fsm.top++] =  fsm.cs;  fsm.cs = 62; goto _again;}}}
	break;
	case 21:
#line 180 "expr.rl"
	{{ fsm.cs =  fsm.stack[-- fsm.top]; {
}goto _again;}}
	break;
	case 22:
#line 182 "expr.rl"
	{{
{ fsm.stack[ fsm.top++] =  fsm.cs;  fsm.cs = 61; goto _again;}}}
	break;
	case 23:
#line 183 "expr.rl"
	{{
{ fsm.stack[ fsm.top++] =  fsm.cs;  fsm.cs = 62; goto _again;}}}
	break;
#line 620 "tmp/scriptExprParse.c"
		}
	}

_again:
	if (  fsm.cs == 0 )
		goto _out;
	if ( ++( fsm.p) != ( fsm.pe) )
		goto _resume;
	_test_eof: {}
	if ( ( fsm.p) == ( fsm.eof) )
	{
	const char *__acts = _exprParse_actions + _exprParse_eof_actions[ fsm.cs];
	unsigned int __nacts = (unsigned int) *__acts++;
	while ( __nacts-- > 0 ) {
		switch ( *__acts++ ) {
	case 2:
#line 16 "expr.rl"
	{
  DEBUG_MARK("- word:b",( fsm.p));
  DEBUG_VAL("===========w",mStart,mEnd);

  if(!isMath) {
  if(mStart<mEnd) { //APPEND_WORD
    if(!scriptExprParsePartCallback(extraData,mStart,mEnd)) {
      {( fsm.p)++; goto _out; }
    }
  }
  
  if(!scriptExprParseWordEndCallback(extraData)) { //APPEND_WORDS
    {( fsm.p)++; goto _out; }
  }
  }
  
  isMath=false;
}
	break;
	case 4:
#line 39 "expr.rl"
	{
  DEBUG_MARK("- - sub:b",( fsm.p));

  mStart=( fsm.p);
  mEnd=( fsm.p);
}
	break;
	case 6:
#line 52 "expr.rl"
	{
  DEBUG_VAL("===========v",mStart,mEnd);

  if(mStart<mEnd) { //APPEND_WORD
    if(!scriptExprParsePartCallback(extraData,mStart,mEnd)) {
      {( fsm.p)++; goto _out; }
    }
  }
  
  const char *a=wStart+1;
  const char *b=( fsm.p);
  
  if(a[0]=='{') {
    a++;
	b--;
  }

  DEBUG_MARK("- - - var:b",( fsm.p));
  DEBUG_VAL("==========vv",a,b);

  if(!scriptExprParseVarCallback(extraData,a,b)) { //APPEND_WORD_VAR
    runErr=true;
    {( fsm.p)++; goto _out; }
  }

  wStart=( fsm.p);
}
	break;
	case 8:
#line 86 "expr.rl"
	{
  const char *a=wStart+1;
  const char *b=( fsm.p)-1;
  
  DEBUG_VAL("===========c",mStart,mEnd);
  DEBUG_MARK("- - - cmd:b",( fsm.p));
  DEBUG_VAL("==========cc",a,b);

  if(mStart<mEnd) { //APPEND_WORD
    if(!scriptExprParsePartCallback(extraData,mStart,mEnd)) {
      {( fsm.p)++; goto _out; }
    }
  }
   
  if(!scriptExprParseCmdCallback(extraData,a,b)) { //APPEND_WORD_CMD
    runErr=true;
    {( fsm.p)++; goto _out; }
  }
  
  wStart=( fsm.p);
}
	break;
	case 10:
#line 115 "expr.rl"
	{
  DEBUG_MARK("- - - qstr:b",( fsm.p));

  wStart=( fsm.p);
}
	break;
	case 12:
#line 128 "expr.rl"
	{
  const char *a=wStart+1;
  const char *b=( fsm.p)-1;
  
  DEBUG_MARK("- - - bstr:b",( fsm.p));
  DEBUG_VAL("==========bb",a,b);

  if(!scriptExprParsePartCallback(extraData,a,b)) { //APPEND_WORD
    {( fsm.p)++; goto _out; }
  }

  wStart=( fsm.p);
  mStart=( fsm.p);
}
	break;
	case 13:
#line 143 "expr.rl"
	{  
  DEBUG_MARK("- - - str_char:b",( fsm.p));

  wStart=( fsm.p);
  mEnd=( fsm.p);
}
	break;
	case 15:
#line 157 "expr.rl"
	{
  quoteParenErr=true;
}
	break;
	case 17:
#line 166 "expr.rl"
	{
  DEBUG_MARK("- - - math:b",( fsm.p));
  DEBUG_VAL("===========m",wStart,( fsm.p));
  
  if(!scriptExprParseMathEndCallback(extraData,wStart,( fsm.p))) {
    {( fsm.p)++; goto _out; }
  }
  
  isMath=true;
  wStart=( fsm.p);
  mStart=( fsm.p);
}
	break;
#line 775 "tmp/scriptExprParse.c"
		}
	}
	}

	_out: {}
	}

#line 303 "expr.rl"

  if(runErr) {
    scriptExprParseRunErrCallback(extraData,fsm.p);
	return false;
  } else if(fsm.top != 0 || quoteParenErr) {
    DEBUG_MARK("paren err",fsm.p);
    scriptExprParseParenErrCallback(extraData,prnStart);
	return false;
  } else if(fsm.cs < 63) {
    DEBUG_MARK("err",fsm.p);
    scriptExprParseErrCallback(extraData,fsm.p);
	return false;
  } 
  
  return true;
}

#ifdef SCRIPT_EXPR_PARSE_TEST
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
  scriptExprParse(text,0);
  free(text);
  printf("done\n");
  return 0;
}
#endif