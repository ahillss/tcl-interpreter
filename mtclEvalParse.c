
#line 1 "eval.rl"
 
#line 248 "eval.rl"


  


#line 253 "eval.rl"

#line 254 "eval.rl"

#line 255 "eval.rl"

#line 256 "eval.rl"


#line 265 "eval.rl"



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
  
#line 64 "tmp/mtclEvalParse.c"
static const char _parse_actions[] = {
	0, 1, 1, 1, 2, 1, 4, 1, 
	5, 1, 17, 1, 18, 1, 19, 1, 
	20, 1, 21, 1, 22, 1, 23, 2, 
	0, 24, 2, 2, 4, 2, 2, 18, 
	2, 3, 5, 2, 4, 2, 2, 5, 
	1, 2, 5, 3, 2, 7, 9, 2, 
	10, 8, 2, 12, 8, 2, 14, 6, 
	2, 16, 6, 2, 17, 1, 2, 17, 
	6, 2, 18, 1, 2, 18, 2, 2, 
	18, 4, 2, 19, 2, 2, 19, 4, 
	3, 2, 10, 8, 3, 2, 12, 8, 
	3, 5, 0, 13, 3, 5, 7, 9, 
	3, 10, 8, 2, 3, 10, 8, 6, 
	3, 12, 8, 2, 3, 12, 8, 6, 
	3, 14, 6, 4, 3, 16, 6, 4, 
	3, 16, 6, 18, 3, 16, 18, 6, 
	3, 17, 3, 5, 3, 17, 6, 4, 
	3, 17, 7, 9, 3, 18, 7, 9, 
	3, 18, 16, 6, 4, 2, 14, 6, 
	4, 4, 2, 16, 6, 4, 4, 2, 
	17, 6, 4, 4, 3, 5, 0, 13, 
	4, 3, 5, 7, 9, 4, 5, 0, 
	13, 3, 4, 5, 0, 13, 18, 4, 
	5, 7, 9, 3, 4, 5, 15, 0, 
	24, 4, 7, 11, 0, 25, 4, 10, 
	8, 6, 4, 4, 10, 8, 7, 9, 
	4, 12, 8, 6, 4, 4, 12, 8, 
	7, 9, 4, 14, 6, 4, 2, 4, 
	16, 6, 4, 2, 4, 16, 6, 18, 
	4, 4, 16, 18, 6, 4, 4, 17, 
	6, 4, 2, 4, 18, 5, 0, 13, 
	4, 18, 16, 6, 4, 4, 19, 14, 
	6, 4, 4, 19, 16, 6, 4, 5, 
	2, 10, 8, 6, 4, 5, 2, 12, 
	8, 6, 4, 5, 3, 5, 15, 0, 
	24, 5, 5, 7, 11, 0, 25, 5, 
	5, 15, 0, 24, 3, 5, 5, 15, 
	0, 24, 18, 5, 10, 8, 6, 4, 
	2, 5, 12, 8, 6, 4, 2, 5, 
	17, 7, 9, 3, 5, 5, 17, 7, 
	11, 0, 25, 5, 18, 3, 5, 0, 
	13, 5, 18, 5, 15, 0, 24, 5, 
	18, 7, 11, 0, 25, 6, 3, 5, 
	7, 11, 0, 25, 6, 5, 7, 11, 
	0, 25, 3, 6, 10, 8, 7, 11, 
	0, 25, 6, 12, 8, 7, 11, 0, 
	25, 6, 18, 3, 5, 15, 0, 24, 
	7, 17, 7, 11, 0, 25, 3, 5
	
};

static const short _parse_key_offsets[] = {
	0, 0, 3, 6, 17, 27, 30, 33, 
	35, 37, 47, 54, 63, 68, 83, 97, 
	104, 111, 116, 118, 130, 142, 154, 166, 
	173, 182, 187, 192, 202, 210, 219, 229, 
	234, 244, 252, 260, 265, 271, 284, 296, 
	301, 306, 314, 323, 333, 341, 349, 357, 
	370, 382, 387, 392, 407, 421, 428, 435, 
	440, 445, 445
};

static const char _parse_trans_keys[] = {
	34, 36, 91, 34, 36, 91, 34, 36, 
	91, 95, 123, 48, 57, 65, 90, 97, 
	122, 34, 36, 91, 95, 48, 57, 65, 
	90, 97, 122, 34, 36, 91, 34, 36, 
	91, 123, 125, 91, 93, 13, 32, 34, 
	35, 36, 59, 91, 123, 9, 10, 9, 
	10, 13, 32, 36, 59, 91, 9, 10, 
	13, 32, 34, 36, 59, 91, 123, 9, 
	10, 13, 32, 59, 9, 10, 13, 32, 
	36, 59, 91, 95, 123, 48, 57, 65, 
	90, 97, 122, 9, 10, 13, 32, 36, 
	59, 91, 95, 48, 57, 65, 90, 97, 
	122, 9, 10, 13, 32, 36, 59, 91, 
	9, 10, 13, 32, 36, 59, 91, 9, 
	10, 13, 32, 59, 10, 59, 13, 32, 
	34, 35, 36, 59, 91, 123, 9, 10, 
	11, 12, 9, 10, 13, 32, 34, 35, 
	36, 59, 91, 123, 11, 12, 9, 10, 
	13, 32, 34, 35, 36, 59, 91, 123, 
	11, 12, 13, 32, 34, 35, 36, 59, 
	91, 123, 9, 10, 11, 12, 9, 10, 
	13, 32, 36, 59, 91, 9, 10, 13, 
	32, 34, 36, 59, 91, 123, 10, 34, 
	36, 59, 91, 10, 34, 36, 59, 91, 
	13, 32, 34, 35, 36, 59, 91, 123, 
	9, 10, 9, 10, 13, 32, 34, 36, 
	59, 91, 9, 10, 13, 32, 34, 36, 
	59, 91, 123, 13, 32, 34, 35, 36, 
	59, 91, 123, 9, 10, 10, 34, 36, 
	59, 91, 13, 32, 34, 35, 36, 59, 
	91, 123, 9, 10, 13, 32, 34, 36, 
	59, 91, 9, 10, 9, 10, 13, 32, 
	34, 36, 59, 91, 9, 10, 13, 32, 
	59, 9, 10, 13, 32, 35, 59, 10, 
	34, 36, 59, 91, 95, 123, 48, 57, 
	65, 90, 97, 122, 10, 34, 36, 59, 
	91, 95, 48, 57, 65, 90, 97, 122, 
	10, 34, 36, 59, 91, 10, 34, 36, 
	59, 91, 9, 10, 13, 32, 34, 36, 
	59, 91, 9, 10, 13, 32, 34, 36, 
	59, 91, 123, 13, 32, 34, 35, 36, 
	59, 91, 123, 9, 10, 9, 10, 13, 
	32, 34, 36, 59, 91, 9, 10, 13, 
	32, 34, 36, 59, 91, 9, 10, 13, 
	32, 34, 36, 59, 91, 10, 34, 36, 
	59, 91, 95, 123, 48, 57, 65, 90, 
	97, 122, 10, 34, 36, 59, 91, 95, 
	48, 57, 65, 90, 97, 122, 10, 34, 
	36, 59, 91, 10, 34, 36, 59, 91, 
	9, 10, 13, 32, 36, 59, 91, 95, 
	123, 48, 57, 65, 90, 97, 122, 9, 
	10, 13, 32, 36, 59, 91, 95, 48, 
	57, 65, 90, 97, 122, 9, 10, 13, 
	32, 36, 59, 91, 9, 10, 13, 32, 
	36, 59, 91, 9, 10, 13, 32, 59, 
	13, 32, 59, 9, 10, 0
};

static const char _parse_single_lengths[] = {
	0, 3, 3, 5, 4, 3, 3, 2, 
	2, 8, 7, 9, 5, 9, 8, 7, 
	7, 5, 2, 8, 10, 10, 8, 7, 
	9, 5, 5, 8, 8, 9, 8, 5, 
	8, 6, 8, 5, 6, 7, 6, 5, 
	5, 8, 9, 8, 8, 8, 8, 7, 
	6, 5, 5, 9, 8, 7, 7, 5, 
	3, 0, 0
};

static const char _parse_range_lengths[] = {
	0, 0, 0, 3, 3, 0, 0, 0, 
	0, 1, 0, 0, 0, 3, 3, 0, 
	0, 0, 0, 2, 1, 1, 2, 0, 
	0, 0, 0, 1, 0, 0, 1, 0, 
	1, 1, 0, 0, 0, 3, 3, 0, 
	0, 0, 0, 1, 0, 0, 0, 3, 
	3, 0, 0, 3, 3, 0, 0, 0, 
	1, 0, 0
};

static const short _parse_index_offsets[] = {
	0, 0, 4, 8, 17, 25, 29, 33, 
	36, 39, 49, 57, 67, 73, 86, 98, 
	106, 114, 120, 123, 134, 146, 158, 169, 
	177, 187, 193, 199, 209, 218, 228, 238, 
	244, 254, 262, 271, 277, 284, 295, 305, 
	311, 317, 326, 336, 346, 355, 364, 373, 
	384, 394, 400, 406, 419, 431, 439, 447, 
	453, 458, 459
};

static const unsigned char _parse_indicies[] = {
	1, 2, 3, 0, 5, 6, 7, 4, 
	5, 6, 7, 8, 9, 8, 8, 8, 
	4, 11, 12, 13, 8, 8, 8, 8, 
	10, 15, 16, 17, 14, 11, 12, 13, 
	10, 19, 20, 18, 22, 23, 21, 25, 
	25, 26, 27, 28, 25, 29, 30, 25, 
	24, 32, 33, 32, 32, 34, 33, 35, 
	31, 37, 38, 37, 37, 39, 40, 38, 
	41, 42, 36, 43, 45, 43, 43, 45, 
	44, 32, 33, 32, 32, 34, 33, 35, 
	46, 47, 46, 46, 46, 31, 49, 50, 
	49, 49, 51, 50, 52, 46, 46, 46, 
	46, 48, 54, 55, 54, 54, 56, 55, 
	57, 53, 49, 50, 49, 49, 51, 50, 
	52, 48, 58, 59, 58, 58, 59, 44, 
	61, 62, 60, 63, 63, 26, 27, 28, 
	65, 29, 30, 63, 64, 24, 67, 68, 
	67, 67, 26, 70, 71, 33, 72, 30, 
	69, 66, 74, 75, 74, 74, 77, 78, 
	79, 38, 80, 81, 76, 73, 82, 82, 
	26, 27, 28, 25, 29, 30, 82, 64, 
	24, 84, 85, 84, 84, 86, 87, 88, 
	83, 90, 91, 90, 90, 92, 93, 94, 
	95, 96, 89, 98, 99, 100, 101, 102, 
	97, 104, 105, 106, 107, 108, 103, 109, 
	109, 110, 111, 6, 112, 7, 113, 109, 
	4, 114, 115, 114, 114, 1, 2, 115, 
	3, 0, 116, 117, 116, 116, 118, 6, 
	117, 7, 119, 4, 120, 120, 110, 121, 
	6, 120, 7, 122, 120, 4, 124, 105, 
	125, 126, 127, 123, 128, 128, 110, 121, 
	6, 112, 7, 122, 128, 4, 112, 112, 
	5, 6, 112, 7, 112, 4, 129, 130, 
	129, 129, 5, 6, 130, 7, 4, 131, 
	132, 131, 131, 133, 60, 134, 135, 134, 
	134, 27, 136, 60, 124, 105, 125, 126, 
	127, 137, 138, 137, 137, 137, 123, 140, 
	141, 142, 143, 144, 137, 137, 137, 137, 
	139, 146, 147, 148, 149, 150, 145, 140, 
	141, 142, 143, 144, 139, 151, 152, 151, 
	151, 1, 2, 152, 3, 0, 153, 154, 
	153, 153, 155, 6, 154, 7, 156, 4, 
	157, 157, 110, 111, 6, 157, 7, 113, 
	157, 4, 158, 159, 158, 158, 5, 6, 
	159, 7, 4, 160, 161, 160, 160, 5, 
	6, 161, 7, 4, 162, 163, 162, 162, 
	5, 6, 163, 7, 4, 104, 105, 106, 
	107, 108, 164, 165, 164, 164, 164, 103, 
	167, 141, 168, 169, 170, 164, 164, 164, 
	164, 166, 172, 147, 173, 174, 175, 171, 
	167, 141, 168, 169, 170, 166, 84, 85, 
	84, 84, 86, 87, 88, 176, 177, 176, 
	176, 176, 83, 179, 180, 179, 179, 181, 
	182, 183, 176, 176, 176, 176, 178, 185, 
	186, 185, 185, 187, 188, 189, 184, 179, 
	180, 179, 179, 181, 182, 183, 178, 190, 
	191, 190, 190, 192, 60, 65, 65, 65, 
	65, 44, 44, 44, 0
};

static const char _parse_trans_targs[] = {
	2, 12, 3, 5, 2, 12, 3, 5, 
	4, 6, 2, 12, 3, 5, 2, 12, 
	3, 5, 7, 7, 57, 8, 8, 58, 
	10, 9, 1, 18, 13, 15, 17, 10, 
	11, 9, 13, 15, 10, 11, 9, 1, 
	13, 15, 17, 11, 0, 9, 14, 16, 
	10, 11, 9, 13, 15, 10, 11, 9, 
	13, 15, 11, 9, 18, 19, 18, 19, 
	20, 56, 10, 21, 22, 20, 23, 13, 
	15, 10, 21, 22, 20, 1, 23, 13, 
	15, 17, 22, 23, 24, 22, 51, 36, 
	53, 23, 24, 22, 25, 51, 36, 53, 
	55, 26, 27, 35, 47, 26, 49, 26, 
	27, 35, 47, 26, 49, 27, 28, 26, 
	33, 44, 29, 30, 29, 30, 41, 46, 
	30, 31, 34, 31, 32, 37, 31, 39, 
	32, 29, 30, 24, 22, 36, 36, 22, 
	36, 38, 40, 31, 32, 35, 37, 31, 
	39, 31, 32, 35, 37, 31, 39, 42, 
	43, 42, 43, 41, 45, 43, 42, 43, 
	42, 43, 29, 30, 48, 50, 26, 27, 
	47, 26, 49, 26, 27, 47, 26, 49, 
	52, 54, 23, 24, 22, 51, 36, 53, 
	23, 24, 22, 51, 36, 53, 24, 22, 
	36
};

static const short _parse_trans_actions[] = {
	0, 0, 44, 193, 11, 11, 140, 335, 
	0, 23, 47, 47, 203, 355, 50, 50, 
	213, 362, 0, 15, 17, 0, 19, 21, 
	32, 0, 163, 1, 168, 341, 275, 9, 
	62, 132, 136, 317, 7, 0, 5, 88, 
	92, 281, 188, 53, 0, 112, 0, 23, 
	47, 100, 198, 203, 355, 50, 108, 208, 
	213, 362, 56, 116, 0, 3, 3, 0, 
	32, 0, 128, 62, 132, 128, 59, 311, 
	376, 41, 0, 5, 41, 173, 38, 183, 
	348, 287, 0, 9, 62, 158, 136, 238, 
	317, 7, 0, 26, 88, 92, 35, 281, 
	188, 0, 3, 0, 44, 3, 193, 11, 
	29, 11, 140, 68, 335, 11, 323, 65, 
	11, 369, 53, 112, 11, 71, 243, 329, 
	11, 65, 369, 11, 29, 140, 68, 335, 
	11, 124, 233, 53, 148, 218, 0, 3, 
	3, 0, 23, 47, 80, 47, 203, 96, 
	355, 50, 84, 50, 213, 104, 362, 53, 
	112, 11, 71, 178, 293, 11, 120, 228, 
	124, 233, 144, 248, 0, 23, 47, 80, 
	203, 96, 355, 50, 84, 213, 104, 362, 
	0, 23, 47, 100, 263, 203, 299, 355, 
	50, 108, 269, 213, 305, 362, 56, 153, 
	223
};

static const short _parse_eof_actions[] = {
	0, 13, 13, 13, 13, 13, 13, 0, 
	0, 0, 132, 5, 112, 132, 198, 208, 
	198, 116, 3, 0, 132, 5, 0, 158, 
	26, 74, 74, 13, 253, 77, 13, 74, 
	13, 13, 258, 148, 3, 74, 74, 74, 
	74, 253, 77, 13, 258, 258, 258, 74, 
	74, 74, 74, 158, 263, 269, 263, 153, 
	0, 0, 0
};

static const int parse_start = 9;
static const int parse_first_final = 9;
static const int parse_error = 0;

static const int parse_en_m_clybrace = 7;
static const int parse_en_m_sqrbrack = 8;
static const int parse_en_main = 9;


#line 308 "eval.rl"
  
  struct {
    int cs;
    const char *p,*pe,*eof;
    int stack[128],top;
  } fsm;
  
  
#line 366 "tmp/mtclEvalParse.c"
	{
	 fsm.cs = parse_start;
	 fsm.top = 0;
	}

#line 316 "eval.rl"
  
  fsm.p=text;
  fsm.pe=text+strlen(text);
  fsm.eof=fsm.pe;
    
  const char *prnStart=0;
  const char *wStart=0;
  const char *mStart=0,*mEnd=0;
  bool runErr=false;
  bool done=false;
  bool quoteParenErr=false;
  
  
#line 386 "tmp/mtclEvalParse.c"
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
	_keys = _parse_trans_keys + _parse_key_offsets[ fsm.cs];
	_trans = _parse_index_offsets[ fsm.cs];

	_klen = _parse_single_lengths[ fsm.cs];
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

	_klen = _parse_range_lengths[ fsm.cs];
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
	_trans = _parse_indicies[_trans];
	 fsm.cs = _parse_trans_targs[_trans];

	if ( _parse_trans_actions[_trans] == 0 )
		goto _again;

	_acts = _parse_actions + _parse_trans_actions[_trans];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 )
	{
		switch ( *_acts++ )
		{
	case 0:
#line 5 "eval.rl"
	{
  prnStart = ( fsm.p);
}
	break;
	case 1:
#line 9 "eval.rl"
	{
  DEBUG_MARK("comment:a",( fsm.p));
}
	break;
	case 2:
#line 13 "eval.rl"
	{
  DEBUG_MARK("comment:b",( fsm.p));
}
	break;
	case 3:
#line 17 "eval.rl"
	{
  DEBUG_MARK("stmt:a",( fsm.p));

  mStart=( fsm.p);
  mEnd=( fsm.p);
}
	break;
	case 4:
#line 24 "eval.rl"
	{
  DEBUG_MARK("stmt:b",( fsm.p));

  if(!mtclEvalParseStmtEndCallback(extraData)) {  //EVAL_WORDS
    runErr=true;
    {( fsm.p)++; goto _out; }
  }
}
	break;
	case 5:
#line 33 "eval.rl"
	{ 
  DEBUG_MARK("- word:a",( fsm.p));

  mStart=( fsm.p);
  mEnd=( fsm.p);
}
	break;
	case 6:
#line 40 "eval.rl"
	{
  DEBUG_MARK("- word:b",( fsm.p));
  DEBUG_VAL("===========w",mStart,mEnd);

  if(mStart<mEnd) { //APPEND_WORD
    char *x=(char*)malloc(mEnd-mStart+1);
	sprintf(x,"%.*s",mEnd-mStart,mStart);
    bool r=mtclEvalParseStrCallback(extraData,mStart,mEnd,x);
    free(x);
	
    if(!r) {
      {( fsm.p)++; goto _out; }
    }
  }
  
  if(!mtclEvalParseWordEndCallback(extraData)) { //APPEND_WORDS
    {( fsm.p)++; goto _out; }
  } 
}
	break;
	case 7:
#line 60 "eval.rl"
	{
  DEBUG_MARK("- - sub:a",( fsm.p));
}
	break;
	case 8:
#line 64 "eval.rl"
	{
  DEBUG_MARK("- - sub:b",( fsm.p));

  mStart=( fsm.p);
  mEnd=( fsm.p);
}
	break;
	case 9:
#line 71 "eval.rl"
	{
  DEBUG_MARK("- - - var:a",( fsm.p));

  wStart=( fsm.p);  
}
	break;
	case 10:
#line 77 "eval.rl"
	{
  DEBUG_VAL("===========v",mStart,mEnd);

  if(mStart<mEnd) { //APPEND_WORD
    char *x=(char*)malloc(mEnd-mStart+1);
	sprintf(x,"%.*s",mEnd-mStart,mStart);
    bool r=mtclEvalParseStrCallback(extraData,mStart,mEnd,x);
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
    bool r=mtclEvalParseCmdCallback(extraData,a,b,x);
    free(x);
	
    if(!r) { //APPEND_WORD_CMD
      runErr=true;
      {( fsm.p)++; goto _out; }
    }
  }
  
  wStart=( fsm.p);
}
	break;
	case 11:
#line 117 "eval.rl"
	{
  DEBUG_MARK("- - - cmd:a",( fsm.p));

  wStart=( fsm.p);  
}
	break;
	case 12:
#line 123 "eval.rl"
	{
  const char *a=wStart+1;
  const char *b=( fsm.p)-1;
  
  DEBUG_VAL("===========c",mStart,mEnd);
  DEBUG_MARK("- - - cmd:b",( fsm.p));
  DEBUG_VAL("==========cc",a,b);

  if(mStart<mEnd) { //APPEND_WORD
    char *x=(char*)malloc(mEnd-mStart+1);
	sprintf(x,"%.*s",mEnd-mStart,mStart);
    bool r=mtclEvalParseStrCallback(extraData,mStart,mEnd,x);
    free(x);
	
    if(!r) {
      {( fsm.p)++; goto _out; }
    }
  }
  {
    char *x=(char*)malloc(b-a+1);
	sprintf(x,"%.*s",b-a,a);
    bool r=mtclEvalParseCmdCallback(extraData,a,b,x);
    free(x);
	
    if(!r) { //APPEND_WORD_CMD
      runErr=true;
      {( fsm.p)++; goto _out; }
    }
  }
  
  wStart=( fsm.p);
}
	break;
	case 13:
#line 156 "eval.rl"
	{
  DEBUG_MARK("- - - qstr:a",( fsm.p));

  wStart=( fsm.p);
  mStart=( fsm.p)+1;  
}
	break;
	case 14:
#line 163 "eval.rl"
	{
  DEBUG_MARK("- - - qstr:b",( fsm.p));

  wStart=( fsm.p);
}
	break;
	case 15:
#line 170 "eval.rl"
	{
  DEBUG_MARK("- - - bstr:a",( fsm.p));

  wStart=( fsm.p);
}
	break;
	case 16:
#line 176 "eval.rl"
	{
  const char *a=wStart+1;
  const char *b=( fsm.p)-1;
  
  DEBUG_MARK("- - - bstr:b",( fsm.p));
  DEBUG_VAL("==========bb",a,b);

  // if(!mtclEvalParseStrCallback(extraData,a,b)) { //APPEND_WORD
  //   fbreak;
  // }
  
    char *x=(char*)malloc(b-a+1);
	sprintf(x,"%.*s",b-a,a);
    bool r=mtclEvalParseStrCallback(extraData,a,b,x);
    free(x);
	
    if(!r) {
      {( fsm.p)++; goto _out; }
    }
	
  wStart=( fsm.p);
  mStart=( fsm.p);
}
	break;
	case 17:
#line 200 "eval.rl"
	{  
  DEBUG_MARK("- - - str_char:b",( fsm.p));

  wStart=( fsm.p); //what was this for?
  mEnd=( fsm.p);
}
	break;
	case 18:
#line 207 "eval.rl"
	{  
  DEBUG_MARK("- - - str_qchar:b",( fsm.p));

  wStart=( fsm.p);
  mEnd=( fsm.p);
}
	break;
	case 20:
#line 218 "eval.rl"
	{{
{ fsm.stack[ fsm.top++] =  fsm.cs;  fsm.cs = 7; goto _again;}}}
	break;
	case 21:
#line 218 "eval.rl"
	{{ fsm.cs =  fsm.stack[-- fsm.top]; {
}goto _again;}}
	break;
	case 22:
#line 219 "eval.rl"
	{{
{ fsm.stack[ fsm.top++] =  fsm.cs;  fsm.cs = 8; goto _again;}}}
	break;
	case 23:
#line 219 "eval.rl"
	{{ fsm.cs =  fsm.stack[-- fsm.top]; {
}goto _again;}}
	break;
	case 24:
#line 221 "eval.rl"
	{{
{ fsm.stack[ fsm.top++] =  fsm.cs;  fsm.cs = 7; goto _again;}}}
	break;
	case 25:
#line 222 "eval.rl"
	{{
{ fsm.stack[ fsm.top++] =  fsm.cs;  fsm.cs = 8; goto _again;}}}
	break;
#line 736 "tmp/mtclEvalParse.c"
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
	const char *__acts = _parse_actions + _parse_eof_actions[ fsm.cs];
	unsigned int __nacts = (unsigned int) *__acts++;
	while ( __nacts-- > 0 ) {
		switch ( *__acts++ ) {
	case 2:
#line 13 "eval.rl"
	{
  DEBUG_MARK("comment:b",( fsm.p));
}
	break;
	case 4:
#line 24 "eval.rl"
	{
  DEBUG_MARK("stmt:b",( fsm.p));

  if(!mtclEvalParseStmtEndCallback(extraData)) {  //EVAL_WORDS
    runErr=true;
    {( fsm.p)++; goto _out; }
  }
}
	break;
	case 6:
#line 40 "eval.rl"
	{
  DEBUG_MARK("- word:b",( fsm.p));
  DEBUG_VAL("===========w",mStart,mEnd);

  if(mStart<mEnd) { //APPEND_WORD
    char *x=(char*)malloc(mEnd-mStart+1);
	sprintf(x,"%.*s",mEnd-mStart,mStart);
    bool r=mtclEvalParseStrCallback(extraData,mStart,mEnd,x);
    free(x);
	
    if(!r) {
      {( fsm.p)++; goto _out; }
    }
  }
  
  if(!mtclEvalParseWordEndCallback(extraData)) { //APPEND_WORDS
    {( fsm.p)++; goto _out; }
  } 
}
	break;
	case 8:
#line 64 "eval.rl"
	{
  DEBUG_MARK("- - sub:b",( fsm.p));

  mStart=( fsm.p);
  mEnd=( fsm.p);
}
	break;
	case 10:
#line 77 "eval.rl"
	{
  DEBUG_VAL("===========v",mStart,mEnd);

  if(mStart<mEnd) { //APPEND_WORD
    char *x=(char*)malloc(mEnd-mStart+1);
	sprintf(x,"%.*s",mEnd-mStart,mStart);
    bool r=mtclEvalParseStrCallback(extraData,mStart,mEnd,x);
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
    bool r=mtclEvalParseCmdCallback(extraData,a,b,x);
    free(x);
	
    if(!r) { //APPEND_WORD_CMD
      runErr=true;
      {( fsm.p)++; goto _out; }
    }
  }
  
  wStart=( fsm.p);
}
	break;
	case 12:
#line 123 "eval.rl"
	{
  const char *a=wStart+1;
  const char *b=( fsm.p)-1;
  
  DEBUG_VAL("===========c",mStart,mEnd);
  DEBUG_MARK("- - - cmd:b",( fsm.p));
  DEBUG_VAL("==========cc",a,b);

  if(mStart<mEnd) { //APPEND_WORD
    char *x=(char*)malloc(mEnd-mStart+1);
	sprintf(x,"%.*s",mEnd-mStart,mStart);
    bool r=mtclEvalParseStrCallback(extraData,mStart,mEnd,x);
    free(x);
	
    if(!r) {
      {( fsm.p)++; goto _out; }
    }
  }
  {
    char *x=(char*)malloc(b-a+1);
	sprintf(x,"%.*s",b-a,a);
    bool r=mtclEvalParseCmdCallback(extraData,a,b,x);
    free(x);
	
    if(!r) { //APPEND_WORD_CMD
      runErr=true;
      {( fsm.p)++; goto _out; }
    }
  }
  
  wStart=( fsm.p);
}
	break;
	case 14:
#line 163 "eval.rl"
	{
  DEBUG_MARK("- - - qstr:b",( fsm.p));

  wStart=( fsm.p);
}
	break;
	case 16:
#line 176 "eval.rl"
	{
  const char *a=wStart+1;
  const char *b=( fsm.p)-1;
  
  DEBUG_MARK("- - - bstr:b",( fsm.p));
  DEBUG_VAL("==========bb",a,b);

  // if(!mtclEvalParseStrCallback(extraData,a,b)) { //APPEND_WORD
  //   fbreak;
  // }
  
    char *x=(char*)malloc(b-a+1);
	sprintf(x,"%.*s",b-a,a);
    bool r=mtclEvalParseStrCallback(extraData,a,b,x);
    free(x);
	
    if(!r) {
      {( fsm.p)++; goto _out; }
    }
	
  wStart=( fsm.p);
  mStart=( fsm.p);
}
	break;
	case 17:
#line 200 "eval.rl"
	{  
  DEBUG_MARK("- - - str_char:b",( fsm.p));

  wStart=( fsm.p); //what was this for?
  mEnd=( fsm.p);
}
	break;
	case 19:
#line 214 "eval.rl"
	{
  quoteParenErr=true;
}
	break;
#line 926 "tmp/mtclEvalParse.c"
		}
	}
	}

	_out: {}
	}

#line 329 "eval.rl"
  if(runErr) {
    mtclEvalParseRunErrCallback(extraData,fsm.p);
  } else if(fsm.top != 0 || quoteParenErr) {
    DEBUG_MARK("paren err",fsm.p);
    mtclEvalParseParenErrCallback(extraData,prnStart);
  } else if(fsm.cs < 9) {
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