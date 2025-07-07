# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required(VERSION 3.50)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("TVPy_proj")

set(PACKAGE_NAME "TVPy_proj")
set(PYPROJECT_NAME "TVPy")

# Convert env vars to CMake variables
set(ENV_PYTHON_PATH $ENV{FOUND_PYTHON_PATH})
set(PYBIND11_INCLUDE $ENV{FOUND_PYBIND11_PATH})
set(pybind11_DIR $ENV{FOUND_PYBIND11_CMAKE_PATH})

# Tell CMake to search here first
set(Python3_ROOT_DIR "${ENV_PYTHON_PATH}" CACHE PATH "Path to Python3 install")
set(Python3_USE_STATIC_LIBS FALSE)

find_package(Python3 REQUIRED COMPONENTS Interpreter Development)
find_package(pybind11 CONFIG REQUIRED)

# Include sub-projects.
add_subdirectory ("TVPy")
