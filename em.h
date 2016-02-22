
#ifdef __EMSCRIPTEN__
#include <emscripten/bind.h>


using namespace emscripten;

#include <stdio.h>
#include <string>

#include "mtcl.h"
#include "mtclEval.h"
#include "mtclCmd.h"


class mtclInterpWrapper {
private:
  struct mtclInterp i;
public:
  mtclInterpWrapper();
  ~mtclInterpWrapper();
  std::string eval(std::string text);
};

#endif
