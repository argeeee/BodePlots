#include <emscripten.h>
#include <emscripten/bind.h>

#include "Bode.h"

// https://emscripten.org/docs/porting/connecting_cpp_and_javascript/embind.html
EMSCRIPTEN_BINDINGS(bode_) {

  class_<Bode>("Bode")
    .constructor<string>()
    .function("getSolution", &Bode::getSolution);

}