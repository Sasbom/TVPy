# TVPy compilation documentation
Documentation v0.1 - Work in progress. | [Head back to Readme](../README.md)

### Building TVPy:

#### Submodules:
First things first, correctly clone including submodules: <br>
When cloning, use `git clone https://github.com/Sasbom/TVPy.git --recurse-submodules`

#### Toolchain compatibility
TVPy is compatible with the following toolchains:

- Visual Studio 2022's compiler, MSVC v143, cxx compiler version 19.44 or above
- GCC 14 and up.
- LLVM Clang linked with either libgc++ or the msvc libraries.

This project uses features of C++23 that have known issues in earlier versions of MSVC compilers, namely `std::format`.
<br>**If you've compiled Unreal engine in Visual before, please set up your environment with the latest compiler to avoid issues.**

This project is NOT built for macOSX.

#### Recommended workflow

Tools you'll need:

- pyenv (both on linux and windows) with some python install that aligns with your target.
- pybind11 on the python install; `python -m pip install pybind11`
- CMake version 3.50 or above (You need to fetch the latest CMake for Visual Studio, if you haven't done so already.)
- A configured C++ compilation environment
- Powershell or Bash (You can get powershell on Linux too)

Powershell:

Run `./pwsh_build_pybind11.ps1`

Bash:

Run `sh bash_build_pybind11.sh`

The scripts are configured to use your configured `python.exe` (win) / `python3` (Linux) to figure out where everything is,
and pybind11's cmake extensions further make things convenient.

Build files are located in `build/TVPy/Release`, with the TVPy.pyi file present for annotation.<br>
A ready made module is available in `build/tvpy_module-[python version]/TVPy`, ready to be put in your python environment.
<br>CMake will also report on this:<br>`[CMake] -- Constructing python module in: C:/Users/Astudio/source/repos/TVPy/build/tvpy_module-3.11.9/TVPy ...`