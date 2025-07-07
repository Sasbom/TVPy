# CMakeList.txt : CMake project for TVPy, include source and define
# project specific logic here.
#

# Add source to this project's executable.
set(MODULE_ENTRY
	"TVPy.cpp"
	"TVPy.hpp"
)

pybind11_add_module(${PYPROJECT_NAME} SHARED ${MODULE_ENTRY})
target_include_directories(${PYPROJECT_NAME} PUBLIC ${PYBIND11_INCLUDE})

target_compile_features(${PYPROJECT_NAME} PUBLIC cxx_std_23)

# TODO: Add tests and install targets if needed.
