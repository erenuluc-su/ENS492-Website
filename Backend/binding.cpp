#include <emscripten/bind.h>
#include "RogersRamanujanCounter.hpp"

using namespace emscripten;

EMSCRIPTEN_BINDINGS(RogersRamanujanCounter) {
   class_<RogersRamanujanCounter>("RogersRamanujanCounter")
      .constructor()
      .function("rrgc", &RogersRamanujanCounter::rrgc)
      .function("rr", &RogersRamanujanCounter::rr)
      .function("getPartnum", &RogersRamanujanCounter::getPartnum)
      .function("getPartitions", &RogersRamanujanCounter::getPartitions)
      ;
}