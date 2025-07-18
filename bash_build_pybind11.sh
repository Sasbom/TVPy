#!/usr/bin/env bash

# TryCommand function: checks if a command exists
try_command() {
    local cmd="$1"
    shift
    local args=("$@")

    if command -v "$cmd" >/dev/null 2>&1; then
        if [ "$WRITE_OUTPUT" = true ]; then
            echo "\"$cmd ${args[*]}\" is valid"
        fi
        return 0
    else
        if [ "$WRITE_OUTPUT" = true ]; then
            echo "Can't find command: $cmd ${args[*]}"
        fi
        return 1
    fi
}

# Flag to control output
WRITE_OUTPUT=true

BUNDLE=false

# Loop through all arguments
for arg in "$@"; do
    if [ "$arg" = "--bundle" ]; then
        BUNDLE=true
    fi
    if [ "$arg" = "-b" ]; then
        BUNDLE=true
    fi
done

if ! try_command python3; then
    echo 'Warning: Command "python3" was not found, exiting...'
    exit 1
else
    echo '"python3" is present!'
fi

python3 ./py_buildutils/module_existence.py pybind11
exit_code=$?
if [ "$exit_code" -eq 1 ]; then
    echo 'Pybind11 dependency could not be resolved.'
    exit 1
else
    echo "Pybind11 module found!"
fi

python3 ./py_buildutils/minimum_version.py 3.7
exit_code=$?
if [ "$exit_code" -eq 1 ]; then
    echo 'Unexpected error occurred while checking python version.'
    exit 1
elif [ "$exit_code" -eq 2 ]; then
    echo "Python version isn't compatible. Consider using a tool like 'pyenv' to set a compatible version."
    exit 1
fi

FOUND_PYTHON_PATH=$(python3 ./py_buildutils/pyfolder.py)
echo "Found Python at: $FOUND_PYTHON_PATH"
FOUND_PYBIND11_PATH=$(python3 ./py_buildutils/pybind11folder.py)
echo "Found pybind11 at: $FOUND_PYBIND11_PATH"
FOUND_PYBIND11_CMAKE_PATH=$(python3 ./py_buildutils/pybind11folder_cmake.py)
echo "Found pybind11 cmake at: $FOUND_PYBIND11_CMAKE_PATH"

# Export paths for downstream tools (optional, depending on your CMake setup)
export FOUND_PYTHON_PATH
export FOUND_PYBIND11_PATH
export FOUND_PYBIND11_CMAKE_PATH

BUNDLE_LIB="False"
if [ "$BUNDLE" = true ]; then
  echo "Bundling libstdc++..."
  BUNDLE_LIB="True"
fi

export BUNDLE_LIB

# export CC=/opt/gcc15/bin/gcc
# export CXX=/opt/gcc15/bin/g++

# Run CMake
cmake -S . -B ./build -DCMAKE_BUILD_TYPE=Release -G Ninja
cmake --build ./build
