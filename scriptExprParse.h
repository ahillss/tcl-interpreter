#ifndef SCRIPTEXPRPARSE
#define SCRIPTEXPRPARSE

#ifndef __cplusplus
#include <stdbool.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

  bool scriptExprParse(const char *text,void *extraData);

  bool scriptExprParsePartCallback(void *data,const char *a,const char *b);
  bool scriptExprParseVarCallback(void *data,const char *a,const char *b);
  bool scriptExprParseCmdCallback(void *data,const char *a,const char *b);
  bool scriptExprParseWordEndCallback(void *data);
  bool scriptExprParseMathEndCallback(void *data,const char *a,const char *b);

  void scriptExprParseErrCallback(void *data,const char *p);
  void scriptExprParseParenErrCallback(void *data,const char *p);
  void scriptExprParseRunErrCallback(void *data,const char *p);

#ifdef __cplusplus
}
#endif

#endif
