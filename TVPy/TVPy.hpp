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
namespace py = pybind11;

#include <tvp_pp/structs/File.hpp>
#include <mio/single_include/mio/mio.hpp>
