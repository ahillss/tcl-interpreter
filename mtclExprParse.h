#ifndef MTCLEXPRPARSE
#define MTCLEXPRPARSE

#ifndef __cplusplus
#include <stdbool.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

  bool mtclExprParse(const char *text,void *extraData);

  bool mtclExprParsePartCallback(void *data,const char *a,const char *b);
  bool mtclExprParseVarCallback(void *data,const char *a,const char *b);
  bool mtclExprParseCmdCallback(void *data,const char *a,const char *b);
  bool mtclExprParseWordEndCallback(void *data);
  bool mtclExprParseMathEndCallback(void *data,const char *a,const char *b);

  void mtclExprParseErrCallback(void *data,const char *p);
  void mtclExprParseParenErrCallback(void *data,const char *p);
  void mtclExprParseRunErrCallback(void *data,const char *p);

#ifdef __cplusplus
}
#endif

#endif
