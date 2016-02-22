
#line 1 "expr.rl"
 
#line 269 "expr.rl"



#line 272 "expr.rl"

#line 273 "expr.rl"

#line 274 "expr.rl"

#line 275 "expr.rl"


#line 284 "expr.rl"


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
  
#line 61 "tmp/mtclExprParse.c"
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
	38, 40, 42, 81, 88, 102, 109, 116, 
	121, 125, 129, 134, 139, 144, 150, 158, 
	165, 171, 182, 190, 198, 206, 214, 222, 
	230, 238, 246, 254, 262, 271, 279, 287, 
	295, 303, 311, 319, 327, 335, 345, 353, 
	361, 369, 377, 385, 394, 402, 410, 418, 
	426, 434, 442, 450, 458, 467, 475, 483, 
	491, 499, 507, 515, 523, 532, 540, 549, 
	557, 565, 573, 582, 590, 598, 608, 616, 
	624, 632, 640, 648, 652, 657, 657
};

static const char _exprParse_trans_keys[] = {
	95, 123, 48, 57, 65, 90, 97, 122, 
	34, 36, 91, 34, 36, 91, 95, 123, 
	48, 57, 65, 90, 97, 122, 34, 36, 
	91, 95, 48, 57, 65, 90, 97, 122, 
	34, 36, 91, 34, 36, 91, 123, 125, 
	91, 93, 13, 32, 33, 34, 36, 37, 
	38, 42, 43, 45, 47, 59, 60, 61, 
	62, 63, 91, 94, 97, 98, 99, 100, 
	101, 102, 104, 105, 108, 109, 110, 112, 
	114, 115, 116, 119, 123, 124, 126, 9, 
	10, 13, 32, 36, 59, 91, 9, 10, 
	13, 32, 36, 59, 91, 95, 9, 10, 
	48, 57, 65, 90, 97, 122, 13, 32, 
	36, 59, 91, 9, 10, 13, 32, 36, 
	59, 91, 9, 10, 13, 32, 61, 9, 
	10, 13, 32, 9, 10, 13, 32, 9, 
	10, 13, 32, 38, 9, 10, 13, 32, 
	42, 9, 10, 13, 32, 47, 9, 10, 
	13, 32, 9, 10, 60, 61, 13, 32, 
	36, 59, 61, 91, 9, 10, 13, 32, 
	36, 59, 91, 9, 10, 13, 32, 9, 
	10, 61, 62, 13, 32, 36, 59, 91, 
	98, 99, 115, 116, 9, 10, 13, 32, 
	36, 59, 91, 115, 9, 10, 13, 32, 
	36, 59, 91, 111, 9, 10, 13, 32, 
	36, 59, 91, 105, 9, 10, 13, 32, 
	36, 59, 91, 110, 9, 10, 13, 32, 
	36, 59, 91, 97, 9, 10, 13, 32, 
	36, 59, 91, 110, 9, 10, 13, 32, 
	36, 50, 59, 91, 9, 10, 13, 32, 
	36, 59, 91, 111, 9, 10, 13, 32, 
	36, 59, 91, 111, 9, 10, 13, 32, 
	36, 59, 91, 108, 9, 10, 13, 32, 
	36, 59, 91, 101, 111, 9, 10, 13, 
	32, 36, 59, 91, 105, 9, 10, 13, 
	32, 36, 59, 91, 115, 9, 10, 13, 
	32, 36, 59, 91, 104, 9, 10, 13, 
	32, 36, 59, 91, 111, 9, 10, 13, 
	32, 36, 59, 91, 117, 9, 10, 13, 
	32, 36, 59, 91, 98, 9, 10, 13, 
	32, 36, 59, 91, 108, 9, 10, 13, 
	32, 36, 59, 91, 101, 9, 10, 13, 
	32, 36, 59, 91, 110, 113, 120, 9, 
	10, 13, 32, 36, 59, 91, 116, 9, 
	10, 13, 32, 36, 59, 91, 105, 9, 
	10, 13, 32, 36, 59, 91, 101, 9, 
	10, 13, 32, 36, 59, 91, 114, 9, 
	10, 13, 32, 36, 59, 91, 112, 9, 
	10, 13, 32, 36, 59, 91, 108, 109, 
	9, 10, 13, 32, 36, 59, 91, 111, 
	9, 10, 13, 32, 36, 59, 91, 111, 
	9, 10, 13, 32, 36, 59, 91, 111, 
	9, 10, 13, 32, 36, 59, 91, 100, 
	9, 10, 13, 32, 36, 59, 91, 121, 
	9, 10, 13, 32, 36, 59, 91, 112, 
	9, 10, 13, 32, 36, 59, 91, 111, 
	9, 10, 13, 32, 36, 59, 91, 116, 
	9, 10, 13, 32, 36, 59, 91, 110, 
	115, 9, 10, 13, 32, 36, 59, 91, 
	116, 9, 10, 13, 32, 36, 59, 91, 
	113, 9, 10, 13, 32, 36, 59, 91, 
	114, 9, 10, 13, 32, 36, 59, 91, 
	111, 9, 10, 13, 32, 36, 59, 91, 
	103, 9, 10, 13, 32, 36, 49, 59, 
	91, 9, 10, 13, 32, 36, 48, 59, 
	91, 9, 10, 13, 32, 36, 59, 91, 
	97, 105, 9, 10, 13, 32, 36, 59, 
	91, 120, 9, 10, 13, 32, 36, 59, 
	91, 101, 105, 9, 10, 13, 32, 36, 
	59, 91, 103, 9, 10, 13, 32, 36, 
	59, 91, 111, 9, 10, 13, 32, 36, 
	59, 91, 119, 9, 10, 13, 32, 36, 
	59, 91, 97, 111, 9, 10, 13, 32, 
	36, 59, 91, 110, 9, 10, 13, 32, 
	36, 59, 91, 117, 9, 10, 13, 32, 
	36, 59, 91, 105, 113, 114, 9, 10, 
	13, 32, 36, 59, 91, 110, 9, 10, 
	13, 32, 36, 59, 91, 97, 9, 10, 
	13, 32, 36, 59, 91, 97, 9, 10, 
	13, 32, 36, 59, 91, 105, 9, 10, 
	13, 32, 36, 59, 91, 100, 9, 10, 
	13, 32, 9, 10, 13, 32, 124, 9, 
	10, 0
};

static const char _exprParse_single_lengths[] = {
	0, 2, 3, 3, 2, 4, 3, 3, 
	2, 2, 37, 5, 6, 5, 5, 3, 
	2, 2, 3, 3, 3, 2, 6, 5, 
	2, 9, 6, 6, 6, 6, 6, 6, 
	6, 6, 6, 6, 7, 6, 6, 6, 
	6, 6, 6, 6, 6, 8, 6, 6, 
	6, 6, 6, 7, 6, 6, 6, 6, 
	6, 6, 6, 6, 7, 6, 6, 6, 
	6, 6, 6, 6, 7, 6, 7, 6, 
	6, 6, 7, 6, 6, 8, 6, 6, 
	6, 6, 6, 2, 3, 0, 0
};

static const char _exprParse_range_lengths[] = {
	0, 3, 0, 0, 3, 3, 0, 0, 
	0, 0, 1, 1, 4, 1, 1, 1, 
	1, 1, 1, 1, 1, 2, 1, 1, 
	2, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 0, 0
};

static const short _exprParse_index_offsets[] = {
	0, 0, 6, 10, 14, 20, 28, 32, 
	36, 39, 42, 81, 88, 99, 106, 113, 
	118, 122, 126, 131, 136, 141, 146, 154, 
	161, 166, 177, 185, 193, 201, 209, 217, 
	225, 233, 241, 249, 257, 266, 274, 282, 
	290, 298, 306, 314, 322, 330, 340, 348, 
	356, 364, 372, 380, 389, 397, 405, 413, 
	421, 429, 437, 445, 453, 462, 470, 478, 
	486, 494, 502, 510, 518, 527, 535, 544, 
	552, 560, 568, 577, 585, 593, 603, 611, 
	619, 627, 635, 643, 647, 652, 653
};

static const char _exprParse_indicies[] = {
	0, 2, 0, 0, 0, 1, 4, 5, 
	6, 3, 8, 9, 10, 7, 11, 12, 
	11, 11, 11, 1, 14, 15, 16, 11, 
	11, 11, 11, 13, 18, 19, 20, 17, 
	14, 15, 16, 13, 22, 23, 21, 25, 
	26, 24, 28, 28, 29, 30, 31, 32, 
	33, 34, 32, 32, 35, 1, 36, 37, 
	38, 32, 39, 32, 40, 41, 42, 43, 
	44, 45, 46, 47, 48, 49, 50, 51, 
	52, 53, 54, 55, 56, 57, 32, 28, 
	27, 59, 59, 60, 1, 61, 59, 58, 
	63, 63, 64, 1, 65, 0, 63, 0, 
	0, 0, 62, 67, 67, 68, 1, 69, 
	67, 66, 63, 63, 64, 1, 65, 63, 
	62, 70, 70, 71, 70, 1, 70, 70, 
	70, 1, 72, 72, 72, 1, 70, 70, 
	71, 70, 1, 70, 70, 71, 70, 1, 
	70, 70, 71, 70, 1, 70, 70, 70, 
	71, 1, 59, 59, 60, 1, 73, 61, 
	59, 58, 74, 74, 60, 1, 61, 74, 
	58, 70, 70, 70, 71, 1, 59, 59, 
	60, 1, 61, 75, 76, 77, 78, 59, 
	58, 59, 59, 60, 1, 61, 73, 59, 
	58, 59, 59, 60, 1, 61, 75, 59, 
	58, 59, 59, 60, 1, 61, 79, 59, 
	58, 59, 59, 60, 1, 61, 73, 59, 
	58, 59, 59, 60, 1, 61, 80, 59, 
	58, 59, 59, 60, 1, 61, 81, 59, 
	58, 74, 74, 60, 73, 1, 61, 74, 
	58, 59, 59, 60, 1, 61, 82, 59, 
	58, 59, 59, 60, 1, 61, 83, 59, 
	58, 59, 59, 60, 1, 61, 73, 59, 
	58, 59, 59, 60, 1, 61, 84, 85, 
	59, 58, 59, 59, 60, 1, 61, 83, 
	59, 58, 59, 59, 60, 1, 61, 86, 
	59, 58, 74, 74, 60, 1, 61, 73, 
	74, 58, 59, 59, 60, 1, 61, 87, 
	59, 58, 59, 59, 60, 1, 61, 88, 
	59, 58, 59, 59, 60, 1, 61, 89, 
	59, 58, 59, 59, 60, 1, 61, 90, 
	59, 58, 59, 59, 60, 1, 61, 73, 
	59, 58, 59, 59, 60, 1, 61, 91, 
	73, 92, 59, 58, 59, 59, 60, 1, 
	61, 93, 59, 58, 59, 59, 60, 1, 
	61, 94, 59, 58, 59, 59, 60, 1, 
	61, 95, 59, 58, 59, 59, 60, 1, 
	61, 73, 59, 58, 59, 59, 60, 1, 
	61, 73, 59, 58, 59, 59, 60, 1, 
	61, 96, 97, 59, 58, 59, 59, 60, 
	1, 61, 98, 59, 58, 59, 59, 60, 
	1, 61, 95, 59, 58, 59, 59, 60, 
	1, 61, 99, 59, 58, 59, 59, 60, 
	1, 61, 73, 59, 58, 59, 59, 60, 
	1, 61, 100, 59, 58, 59, 59, 60, 
	1, 61, 101, 59, 58, 59, 59, 60, 
	1, 61, 102, 59, 58, 59, 59, 60, 
	1, 61, 73, 59, 58, 59, 59, 60, 
	1, 61, 103, 104, 59, 58, 74, 74, 
	60, 1, 61, 73, 74, 58, 59, 59, 
	60, 1, 61, 105, 59, 58, 59, 59, 
	60, 1, 61, 102, 59, 58, 59, 59, 
	60, 1, 61, 106, 59, 58, 59, 59, 
	60, 1, 61, 107, 59, 58, 74, 74, 
	60, 108, 1, 61, 74, 58, 59, 59, 
	60, 73, 1, 61, 59, 58, 59, 59, 
	60, 1, 61, 109, 79, 59, 58, 59, 
	59, 60, 1, 61, 73, 59, 58, 59, 
	59, 60, 1, 61, 110, 73, 59, 58, 
	74, 74, 60, 1, 61, 73, 74, 58, 
	59, 59, 60, 1, 61, 111, 59, 58, 
	59, 59, 60, 1, 61, 73, 59, 58, 
	59, 59, 60, 1, 61, 112, 113, 59, 
	58, 59, 59, 60, 1, 61, 99, 59, 
	58, 59, 59, 60, 1, 61, 112, 59, 
	58, 59, 59, 60, 1, 61, 114, 105, 
	115, 59, 58, 59, 59, 60, 1, 61, 
	86, 59, 58, 59, 59, 60, 1, 61, 
	112, 59, 58, 59, 59, 60, 1, 61, 
	114, 59, 58, 59, 59, 60, 1, 61, 
	116, 59, 58, 59, 59, 60, 1, 61, 
	90, 59, 58, 117, 117, 117, 1, 70, 
	70, 71, 70, 1, 1, 1, 0
};

static const char _exprParse_trans_targs[] = {
	12, 0, 14, 3, 17, 4, 6, 3, 
	17, 4, 6, 5, 7, 3, 17, 4, 
	6, 3, 17, 4, 6, 8, 8, 85, 
	9, 9, 86, 11, 10, 15, 2, 1, 
	16, 18, 19, 20, 21, 22, 24, 13, 
	25, 33, 36, 40, 45, 51, 56, 60, 
	64, 68, 70, 72, 74, 77, 80, 81, 
	83, 84, 11, 10, 1, 13, 11, 10, 
	1, 13, 11, 10, 1, 13, 10, 16, 
	10, 23, 10, 26, 27, 28, 30, 29, 
	31, 32, 34, 35, 37, 38, 39, 41, 
	42, 43, 44, 46, 50, 47, 48, 49, 
	52, 54, 53, 55, 57, 58, 59, 61, 
	62, 63, 65, 66, 67, 69, 71, 73, 
	75, 76, 78, 79, 82, 10
};

static const char _exprParse_trans_actions[] = {
	0, 0, 17, 0, 0, 23, 77, 5, 
	5, 64, 104, 0, 17, 26, 26, 82, 
	110, 29, 29, 87, 117, 0, 9, 11, 
	0, 13, 15, 1, 0, 20, 44, 48, 
	20, 20, 20, 20, 20, 20, 20, 92, 
	20, 20, 20, 20, 20, 20, 20, 20, 
	20, 20, 20, 20, 20, 20, 20, 20, 
	72, 20, 3, 38, 60, 98, 26, 52, 
	82, 110, 29, 56, 87, 117, 41, 0, 
	32, 3, 68, 3, 3, 3, 3, 3, 
	3, 3, 3, 3, 3, 3, 3, 3, 
	3, 3, 3, 3, 3, 3, 3, 3, 
	3, 3, 3, 3, 3, 3, 3, 3, 
	3, 3, 3, 3, 3, 3, 3, 3, 
	3, 3, 3, 3, 3, 35
};

static const char _exprParse_eof_actions[] = {
	0, 0, 7, 7, 7, 7, 7, 7, 
	0, 0, 0, 38, 52, 56, 52, 41, 
	41, 32, 41, 41, 41, 41, 38, 68, 
	41, 38, 38, 38, 38, 38, 38, 38, 
	68, 38, 38, 38, 38, 38, 38, 68, 
	38, 38, 38, 38, 38, 38, 38, 38, 
	38, 38, 38, 38, 38, 38, 38, 38, 
	38, 38, 38, 38, 38, 68, 38, 38, 
	38, 38, 68, 38, 38, 38, 38, 68, 
	38, 38, 38, 38, 38, 38, 38, 38, 
	38, 38, 38, 35, 41, 0, 0
};

static const int exprParse_start = 10;
static const int exprParse_first_final = 10;
static const int exprParse_error = 0;

static const int exprParse_en_m_clybrace = 8;
static const int exprParse_en_m_sqrbrack = 9;
static const int exprParse_en_main = 10;


#line 326 "expr.rl"
  
  struct {
    int cs;
    const char *p,*pe,*eof;
    int stack[128],top;
  } fsm;
  
  
#line 376 "tmp/mtclExprParse.c"
	{
	 fsm.cs = exprParse_start;
	 fsm.top = 0;
	}

#line 334 "expr.rl"
  
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
  
  
#line 397 "tmp/mtclExprParse.c"
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
      char *x=(char*)malloc(mEnd-mStart+1);
	  sprintf(x,"%.*s",mEnd-mStart,mStart);
	  bool r=mtclExprParseStrCallback(extraData,mStart,mEnd,x);
	  free(x);
	  
      if(!r) {
        {( fsm.p)++; goto _out; }
      }
    }
  
    if(!mtclExprParseWordEndCallback(extraData)) { //APPEND_WORDS
      {( fsm.p)++; goto _out; }
    }
  }
  
  isMath=false;
}
	break;
	case 3:
#line 40 "expr.rl"
	{
  DEBUG_MARK("- - sub:a",( fsm.p));
}
	break;
	case 4:
#line 44 "expr.rl"
	{
  DEBUG_MARK("- - sub:b",( fsm.p));

  mStart=( fsm.p);
  mEnd=( fsm.p);
}
	break;
	case 5:
#line 51 "expr.rl"
	{
  DEBUG_MARK("- - - var:a",( fsm.p));

  wStart=( fsm.p);  
}
	break;
	case 6:
#line 57 "expr.rl"
	{
  DEBUG_VAL("===========v",mStart,mEnd);

  if(mStart<mEnd) { //APPEND_WORD
    char *x=(char*)malloc(mEnd-mStart+1);
	sprintf(x,"%.*s",mEnd-mStart,mStart);
	bool r=mtclExprParseStrCallback(extraData,mStart,mEnd,x);
	free(x);
	
    if(!r) {
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

  {
    char *x=(char*)malloc(6+b-a+1);
	sprintf(x,"set {%.*s}",b-a,a);
    bool r=mtclExprParseCmdCallback(extraData,a,b,x);
    free(x);
	
    if(!r) { //APPEND_WORD_VAR
      runErr=true;
      {( fsm.p)++; goto _out; }
    }
  }

  wStart=( fsm.p);
}
	break;
	case 7:
#line 97 "expr.rl"
	{
  DEBUG_MARK("- - - cmd:a",( fsm.p));

  wStart=( fsm.p);  
}
	break;
	case 8:
#line 103 "expr.rl"
	{
  const char *a=wStart+1;
  const char *b=( fsm.p)-1;
  
  DEBUG_VAL("===========c",mStart,mEnd);
  DEBUG_MARK("- - - cmd:b",( fsm.p));
  DEBUG_VAL("==========cc",a,b);

  if(mStart<mEnd) { //APPEND_WORD
    char *x=(char*)malloc(mEnd-mStart+1);
	sprintf(x,"%.*s",mEnd-mStart,mStart);
	bool r=mtclExprParseStrCallback(extraData,mStart,mEnd,x);
	free(x);
	
    if(!r) {
      {( fsm.p)++; goto _out; }
    }
  }
  
  {  
    char *x=(char*)malloc(b-a+1);
	sprintf(x,"%.*s",b-a,a);
	bool r=mtclExprParseCmdCallback(extraData,a,b,x);
	free(x);
	
    if(!r) { //APPEND_WORD_CMD
      runErr=true;
      {( fsm.p)++; goto _out; }
    }
  }
  
  wStart=( fsm.p);
}
	break;
	case 9:
#line 137 "expr.rl"
	{
  DEBUG_MARK("- - - qstr:a",( fsm.p));

  wStart=( fsm.p);
  mStart=( fsm.p)+1;  
}
	break;
	case 10:
#line 144 "expr.rl"
	{
  DEBUG_MARK("- - - qstr:b",( fsm.p));

  wStart=( fsm.p);
}
	break;
	case 11:
#line 151 "expr.rl"
	{
  DEBUG_MARK("- - - bstr:a",( fsm.p));

  wStart=( fsm.p);
}
	break;
	case 12:
#line 157 "expr.rl"
	{
  const char *a=wStart+1;
  const char *b=( fsm.p)-1;
  
  DEBUG_MARK("- - - bstr:b",( fsm.p));
  DEBUG_VAL("==========bb",a,b);
  
  {
    char *x=(char*)malloc(b-a+1);
	sprintf(x,"%.*s",b-a,a);
	bool r=mtclExprParseStrCallback(extraData,a,b,x);
	free(x);
	
    if(!r) { //APPEND_WORD
      {( fsm.p)++; goto _out; }
    }
  }

  wStart=( fsm.p);
  mStart=( fsm.p);
}
	break;
	case 13:
#line 179 "expr.rl"
	{  
  DEBUG_MARK("- - - str_char:b",( fsm.p));

  //wStart=fpc; //what was this for?
  mEnd=( fsm.p);
}
	break;
	case 14:
#line 186 "expr.rl"
	{  
  DEBUG_MARK("- - - str_qchar:b",( fsm.p));

  wStart=( fsm.p);
  mEnd=( fsm.p);
}
	break;
	case 16:
#line 197 "expr.rl"
	{
  DEBUG_MARK("- - - math:a",( fsm.p));
  wStart=( fsm.p);
}
	break;
	case 17:
#line 202 "expr.rl"
	{
  DEBUG_MARK("- - - math:b",( fsm.p));
  DEBUG_VAL("===========m",wStart,( fsm.p));
  
  {
    const char *a=wStart;
	const char *b=( fsm.p);
	
    char *x=(char*)malloc(b-a+1);
	sprintf(x,"%.*s",b-a,a);
	bool r=mtclExprParseMathEndCallback(extraData,a,b,x);
	free(x);
	
    if(!r) {
      {( fsm.p)++; goto _out; }
    }
  }
  
  isMath=true;
  wStart=( fsm.p);
  mStart=( fsm.p);
}
	break;
	case 18:
#line 225 "expr.rl"
	{{
{ fsm.stack[ fsm.top++] =  fsm.cs;  fsm.cs = 8; goto _again;}}}
	break;
	case 19:
#line 225 "expr.rl"
	{{ fsm.cs =  fsm.stack[-- fsm.top]; {
}goto _again;}}
	break;
	case 20:
#line 226 "expr.rl"
	{{
{ fsm.stack[ fsm.top++] =  fsm.cs;  fsm.cs = 9; goto _again;}}}
	break;
	case 21:
#line 226 "expr.rl"
	{{ fsm.cs =  fsm.stack[-- fsm.top]; {
}goto _again;}}
	break;
	case 22:
#line 228 "expr.rl"
	{{
{ fsm.stack[ fsm.top++] =  fsm.cs;  fsm.cs = 8; goto _again;}}}
	break;
	case 23:
#line 229 "expr.rl"
	{{
{ fsm.stack[ fsm.top++] =  fsm.cs;  fsm.cs = 9; goto _again;}}}
	break;
#line 750 "tmp/mtclExprParse.c"
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
      char *x=(char*)malloc(mEnd-mStart+1);
	  sprintf(x,"%.*s",mEnd-mStart,mStart);
	  bool r=mtclExprParseStrCallback(extraData,mStart,mEnd,x);
	  free(x);
	  
      if(!r) {
        {( fsm.p)++; goto _out; }
      }
    }
  
    if(!mtclExprParseWordEndCallback(extraData)) { //APPEND_WORDS
      {( fsm.p)++; goto _out; }
    }
  }
  
  isMath=false;
}
	break;
	case 4:
#line 44 "expr.rl"
	{
  DEBUG_MARK("- - sub:b",( fsm.p));

  mStart=( fsm.p);
  mEnd=( fsm.p);
}
	break;
	case 6:
#line 57 "expr.rl"
	{
  DEBUG_VAL("===========v",mStart,mEnd);

  if(mStart<mEnd) { //APPEND_WORD
    char *x=(char*)malloc(mEnd-mStart+1);
	sprintf(x,"%.*s",mEnd-mStart,mStart);
	bool r=mtclExprParseStrCallback(extraData,mStart,mEnd,x);
	free(x);
	
    if(!r) {
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

  {
    char *x=(char*)malloc(6+b-a+1);
	sprintf(x,"set {%.*s}",b-a,a);
    bool r=mtclExprParseCmdCallback(extraData,a,b,x);
    free(x);
	
    if(!r) { //APPEND_WORD_VAR
      runErr=true;
      {( fsm.p)++; goto _out; }
    }
  }

  wStart=( fsm.p);
}
	break;
	case 8:
#line 103 "expr.rl"
	{
  const char *a=wStart+1;
  const char *b=( fsm.p)-1;
  
  DEBUG_VAL("===========c",mStart,mEnd);
  DEBUG_MARK("- - - cmd:b",( fsm.p));
  DEBUG_VAL("==========cc",a,b);

  if(mStart<mEnd) { //APPEND_WORD
    char *x=(char*)malloc(mEnd-mStart+1);
	sprintf(x,"%.*s",mEnd-mStart,mStart);
	bool r=mtclExprParseStrCallback(extraData,mStart,mEnd,x);
	free(x);
	
    if(!r) {
      {( fsm.p)++; goto _out; }
    }
  }
  
  {  
    char *x=(char*)malloc(b-a+1);
	sprintf(x,"%.*s",b-a,a);
	bool r=mtclExprParseCmdCallback(extraData,a,b,x);
	free(x);
	
    if(!r) { //APPEND_WORD_CMD
      runErr=true;
      {( fsm.p)++; goto _out; }
    }
  }
  
  wStart=( fsm.p);
}
	break;
	case 10:
#line 144 "expr.rl"
	{
  DEBUG_MARK("- - - qstr:b",( fsm.p));

  wStart=( fsm.p);
}
	break;
	case 12:
#line 157 "expr.rl"
	{
  const char *a=wStart+1;
  const char *b=( fsm.p)-1;
  
  DEBUG_MARK("- - - bstr:b",( fsm.p));
  DEBUG_VAL("==========bb",a,b);
  
  {
    char *x=(char*)malloc(b-a+1);
	sprintf(x,"%.*s",b-a,a);
	bool r=mtclExprParseStrCallback(extraData,a,b,x);
	free(x);
	
    if(!r) { //APPEND_WORD
      {( fsm.p)++; goto _out; }
    }
  }

  wStart=( fsm.p);
  mStart=( fsm.p);
}
	break;
	case 13:
#line 179 "expr.rl"
	{  
  DEBUG_MARK("- - - str_char:b",( fsm.p));

  //wStart=fpc; //what was this for?
  mEnd=( fsm.p);
}
	break;
	case 15:
#line 193 "expr.rl"
	{
  quoteParenErr=true;
}
	break;
	case 17:
#line 202 "expr.rl"
	{
  DEBUG_MARK("- - - math:b",( fsm.p));
  DEBUG_VAL("===========m",wStart,( fsm.p));
  
  {
    const char *a=wStart;
	const char *b=( fsm.p);
	
    char *x=(char*)malloc(b-a+1);
	sprintf(x,"%.*s",b-a,a);
	bool r=mtclExprParseMathEndCallback(extraData,a,b,x);
	free(x);
	
    if(!r) {
      {( fsm.p)++; goto _out; }
    }
  }
  
  isMath=true;
  wStart=( fsm.p);
  mStart=( fsm.p);
}
	break;
#line 951 "tmp/mtclExprParse.c"
		}
	}
	}

	_out: {}
	}

#line 348 "expr.rl"

  if(runErr) {
    mtclExprParseRunErrCallback(extraData,fsm.p);
	return false;
  } else if(fsm.top != 0 || quoteParenErr) {
    DEBUG_MARK("paren err",fsm.p);
    mtclExprParseParenErrCallback(extraData,prnStart);
	return false;
  } else if(fsm.cs < 10) {
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