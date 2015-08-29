
#include "script.h"
#include "scriptCmd.h"
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

void evalFile(struct scriptInterp *i,const char *fn) {
  char *buf=stringFromFile(fn);

  if(!buf) {
    return;
  }

  if(scriptEval(i,buf) != SCRIPT_OK) {
    printf("%s\n", i->result);
  }

  free(buf);
}

int runREPL(struct scriptInterp *interp) {
  while(1) {
    char clibuf[1024];
    int retcode;

    printf("script> ");
    fflush(stdout);

    if(fgets(clibuf,1024,stdin) == NULL) {
      break;
    }

    retcode = scriptEval(interp,clibuf);

    if (interp->result[0] != '\0') {
      printf("[%d] %s\n", retcode, interp->result);
    }
  }

  return 0;
}

int main(int argc, char **argv) {
  struct scriptInterp i;
  scriptInitInterp(&i);
  scriptRegisterCoreCommands(&i);

  // if(argc == 1) {
  //   runREPL(&i);
  // } else if(argc == 2) {
  //   evalFile(&i,argv[1]);
  // }

  evalFile(&i,"common.tcl");
  evalFile(&i,"tests/b.tcl");
  // runREPL(&i);


#if defined(_MSC_VER) && defined(_DEBUG)
  system("pause");
#endif

  return 0;
}
