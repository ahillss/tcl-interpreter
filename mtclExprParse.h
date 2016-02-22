#ifndef MTCLEXPRPARSE
#define MTCLEXPRPARSE

#ifndef __cplusplus
#include <stdbool.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

  bool mtclExprParse(const char *text,void *extraData);

  bool mtclExprParseStrCallback(void *data,const char *a,const char *b,const char *x);
  bool mtclExprParseCmdCallback(void *data,const char *a,const char *b,const char *x);
  bool mtclExprParseWordEndCallback(void *data);
  bool mtclExprParseMathEndCallback(void *data,const char *a,const char *b,const char *x);

  void mtclExprParseErrCallback(void *data,const char *p);
  void mtclExprParseParenErrCallback(void *data,const char *p);
  void mtclExprParseRunErrCallback(void *data,const char *p);

#ifdef __cplusplus
}
#endif

#endif
