#include "em.h"

#ifdef __EMSCRIPTEN__

mtclInterpWrapper::mtclInterpWrapper() {
  mtclInitInterp(&i);
  mtclRegisterCoreCommands(&i);
}

mtclInterpWrapper::~mtclInterpWrapper() {
  mtclUninitInterp(&i);
}

std::string mtclInterpWrapper::eval(std::string text) {
  mtclEval(&i,text.c_str());
  return i.result;
}

EMSCRIPTEN_BINDINGS(my_module) {
  class_<mtclInterpWrapper>("mtclInterpWrapper")
    .constructor<>()
    .function("eval", &mtclInterpWrapper::eval)
    ;
}


#endif
