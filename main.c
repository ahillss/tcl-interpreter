
#include "mtcl.h"
#include "mtclCmd.h"

#include "mtclEval.h"

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

void evalFile(struct mtclInterp *i,const char *fn) {
  char *buf=stringFromFile(fn);

  if(!buf) {
    return;
  }

  if(mtclEval(i,buf) != MTCL_OK) {
    printf("%s\n", i->result);
  }

  free(buf);
}

int runREPL(struct mtclInterp *interp) {
  while(1) {
    char clibuf[1024];
    int retcode;

    printf("mtcl> ");
    fflush(stdout);

    if(fgets(clibuf,1024,stdin) == NULL) {
      break;
    }

    retcode = mtclEval(interp,clibuf);

    if (interp->result[0] != '\0') {
      printf("[%d] %s\n", retcode, interp->result);
    }
  }

  return 0;
}

int main(int argc, char **argv) {
  struct mtclInterp i;
  mtclInitInterp(&i);
  mtclRegisterCoreCommands(&i);
  evalFile(&i,"common.tcl");
  if(argc == 1) {
    runREPL(&i);
  } else if(argc == 2) {
    evalFile(&i,argv[1]);
  }


  // evalFile(&i,"tests/b.tcl");
  // runREPL(&i);

  mtclUninitInterp(&i);
#if defined(_MSC_VER) && defined(_DEBUG)
  system("pause");
#endif

  return 0;
}
