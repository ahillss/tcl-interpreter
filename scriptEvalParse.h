#ifndef SCRIPTEVALPARSE_H
#define SCRIPTEVALPARSE_H

#ifndef __cplusplus
#include <stdbool.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

  void scriptEvalParse(const char *text,void *extraData);

  bool scriptEvalParsePartCallback(void *data,const char *a,const char *b);
  bool scriptEvalParseVarCallback(void *data,const char *a,const char *b);
  bool scriptEvalParseCmdCallback(void *data,const char *a,const char *b);
  bool scriptEvalParseWordEndCallback(void *data);
  bool scriptEvalParseStmtEndCallback(void *data);

  void scriptEvalParseErrCallback(void *data,const char *p);
  void scriptEvalParseParenErrCallback(void *data,const char *p);
  void scriptEvalParseRunErrCallback(void *data,const char *p);
#ifdef __cplusplus
}
#endif

#endif
