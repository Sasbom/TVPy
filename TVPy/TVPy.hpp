// TVPy.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <string_view>
#include <filesystem>
#include <vector>
#include <exception>
#include <format>
#include <optional>
#include <cstdint>

#define PYBIND11_CPP20
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>
using namespace pybind11::literals;
namespace py = pybind11;

#include <tvp_pp/structs/File.hpp>
#include <mio/single_include/mio/mio.hpp>

#define EMPTY_FUNC [](){}

// enum helpers

inline void register_blendmode_enum(py::module_& m) {
#ifdef DIFFERENCE // on msvc, difference is a macro in winuser.
#define RESTORE_DIFFERENCE
#undef DIFFERENCE
#endif
    py::enum_<blendmode_t>(m, "BlendMode")
        .value("COLOR", blendmode_t::COLOR)
        .value("BEHIND", blendmode_t::BEHIND)
        .value("ERASE", blendmode_t::ERASE)
        .value("SHADE", blendmode_t::SHADE)
        .value("LIGHT", blendmode_t::LIGHT)
        .value("COLORIZE", blendmode_t::COLORIZE)
        .value("TINT", blendmode_t::TINT)
        .value("SATURATE2", blendmode_t::SATURATE2)
        .value("VALUE", blendmode_t::VALUE)
        .value("ADD", blendmode_t::ADD)
        .value("SUB", blendmode_t::SUB)
        .value("MULTIPLY", blendmode_t::MULTIPLY)
        .value("SCREEN", blendmode_t::SCREEN)
        .value("REPLACE", blendmode_t::REPLACE)
        .value("SUBSTITUTE", blendmode_t::SUBSTITUTE)
        .value("DIFFERENCE", blendmode_t::DIFFERENCE)
        .value("DIVIDE", blendmode_t::DIVIDE)
        .value("OVERLAY", blendmode_t::OVERLAY)
        .value("OVERLAY2", blendmode_t::OVERLAY2)
        .value("DODGE", blendmode_t::DODGE)
        .value("BURN", blendmode_t::BURN)
        .value("HARDLIGHT", blendmode_t::HARDLIGHT)
        .value("SOFTLIGHT", blendmode_t::SOFTLIGHT)
        .value("GRAINEXTRACT", blendmode_t::GRAINEXTRACT)
        .value("GRAINMERGE", blendmode_t::GRAINMERGE)
        .value("SUBTRACT", blendmode_t::SUBTRACT)
        .value("DARKENONLY", blendmode_t::DARKENONLY)
        .value("LIGHTENONLY", blendmode_t::LIGHTENONLY)
        .value("ALPHADIFF", blendmode_t::ALPHADIFF);
#ifdef RESTORE_DIFFERENCE
#define DIFFERENCE 11
#undef RESTORE_DIFFERENCE
#endif
}

inline void register_repeat_enum(py::module_& m) {
    py::enum_<repeat_t>(m, "RepeatMode")
        .value("NONE", repeat_t::NONE)
        .value("REPEAT", repeat_t::REPEAT)
        .value("PINGPONG", repeat_t::PINGPONG)
        .value("HOLD", repeat_t::HOLD);
}