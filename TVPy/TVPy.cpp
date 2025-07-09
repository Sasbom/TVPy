#include "TVPy.hpp"
#include "structs/TVPyCommon.hpp"

PYBIND11_MODULE(TVPy, m) {
    register_blendmode_enum(m);
    register_repeat_enum(m);
    register_tvpyfile(m);
    register_tvpfileinfo(m);
    register_tvpclip(m);
    register_tvplayer(m);
}

