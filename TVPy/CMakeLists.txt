# CMakeList.txt : CMake project for TVPy, include source and define
# project specific logic here.
#

# Add source to this project's executable.
set(MODULE_ENTRY
	"TVPy.cpp"
	"TVPy.hpp"
	"structs/TVPyFile.cpp"
	"structs/TVPyFile.hpp"
	"structs/TVPyClip.cpp"
	"structs/TVPyClip.hpp"
	"structs/TVPyLayer.cpp"
	"structs/TVPyLayer.hpp"
	"structs/TVPyFileInfo.cpp"
	"structs/TVPyFileInfo.hpp"
	"structs/TVPyCommon.hpp"
)

pybind11_add_module(${PYPROJECT_NAME} SHARED ${MODULE_ENTRY})
target_include_directories(${PYPROJECT_NAME} PUBLIC ${PYBIND11_INCLUDE} "${CMAKE_SOURCE_DIR}/TVPP_PP")

target_link_libraries(${PYPROJECT_NAME} PRIVATE TVPP_PP)

target_compile_features(${PYPROJECT_NAME} PUBLIC cxx_std_23)

# Copy TVPy.pyi to the build directory
add_custom_command(
    TARGET ${PYPROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/TVPy/TVPy.pyi"
        "$<TARGET_FILE_DIR:${PYPROJECT_NAME}>/TVPy.pyi"
    COMMENT "Copying Pyhon Interface File TVPy.pyi to module output directory\n"
)

# Construct module.
add_custom_command(
    TARGET ${PYPROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/TVPy/TVPy.pyi"
        "$<TARGET_FILE_DIR:${PYPROJECT_NAME}>/../../module/TVPy.pyi"
    COMMENT "Constructing python module in build/module/TVPy\n"
)
add_custom_command(
    TARGET ${PYPROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<TARGET_FILE:${PYPROJECT_NAME}>"
        "$<TARGET_FILE_DIR:${PYPROJECT_NAME}>/../../module/$<TARGET_FILE_NAME:${PYPROJECT_NAME}>"
)
add_custom_command(
    TARGET ${PYPROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/TVPy/__init__.py"
        "$<TARGET_FILE_DIR:${PYPROJECT_NAME}>/../../module/__init__.py"
    COMMENT "Finishing building module.\n"
)