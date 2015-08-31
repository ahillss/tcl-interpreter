#ifndef MTCLEVALPARSE_H
#define MTCLEVALPARSE_H

#ifndef __cplusplus
#include <stdbool.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

  void mtclEvalParse(const char *text,void *extraData);

  bool mtclEvalParsePartCallback(void *data,const char *a,const char *b);
  bool mtclEvalParseVarCallback(void *data,const char *a,const char *b);
  bool mtclEvalParseCmdCallback(void *data,const char *a,const char *b);
  bool mtclEvalParseWordEndCallback(void *data);
  bool mtclEvalParseStmtEndCallback(void *data);

  void mtclEvalParseErrCallback(void *data,const char *p);
  void mtclEvalParseParenErrCallback(void *data,const char *p);
  void mtclEvalParseRunErrCallback(void *data,const char *p);
#ifdef __cplusplus
}
#endif

#endif
