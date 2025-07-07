#include "TVPy.hpp"
#include "structs/TVPyCommon.hpp"

PYBIND11_MODULE(TVPy, m) {
    blendmode_enum(m);
    repeat_enum(m);
    register_tvpyfile(m);
}

