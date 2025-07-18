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

if(LINUX)
    target_compile_options(TVPP_PP PRIVATE -fPIC)

    # Look for libstdc++.so in ./libs/...  
    # This is mainly there for distros that don't support the latest c++ (many)
    set_target_properties(${PYPROJECT_NAME} PROPERTIES
        INSTALL_RPATH "$ORIGIN/libs"
        BUILD_WITH_INSTALL_RPATH TRUE
    )
endif()

# Copy TVPy.pyi to the build directory
add_custom_command(
    TARGET ${PYPROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/TVPy/TVPy.pyi"
        "$<TARGET_FILE_DIR:${PYPROJECT_NAME}>/TVPy.pyi"
    COMMENT "Copying Pyhon Interface File TVPy.pyi to target output directory"
)

# Construct module.
message(STATUS "Constructing python module in: ${CMAKE_SOURCE_DIR}/build/tvpy_module-${Python3_VERSION}/TVPy ...")
add_custom_command(
    TARGET ${PYPROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/TVPy/TVPy.pyi"
        "$<TARGET_FILE_DIR:${PYPROJECT_NAME}>/../../tvpy_module-${Python3_VERSION}/TVPy/TVPy.pyi"
)
add_custom_command(
    TARGET ${PYPROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
       "${CMAKE_SOURCE_DIR}/LICENSE"
        "$<TARGET_FILE_DIR:${PYPROJECT_NAME}>/../../tvpy_module-${Python3_VERSION}/TVPy/LICENSE"
)
add_custom_command(
    TARGET ${PYPROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<TARGET_FILE:${PYPROJECT_NAME}>"
        "$<TARGET_FILE_DIR:${PYPROJECT_NAME}>/../../tvpy_module-${Python3_VERSION}/TVPy/$<TARGET_FILE_NAME:${PYPROJECT_NAME}>"
)
add_custom_command(
    TARGET ${PYPROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/TVPy/__init__.py"
        "$<TARGET_FILE_DIR:${PYPROJECT_NAME}>/../../tvpy_module-${Python3_VERSION}/TVPy/__init__.py"
        COMMENT "Constructed python module."
)

if(LINUX)
if(BUNDLE_LIBCPP STREQUAL "True")
add_custom_command(
    TARGET ${PYPROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/TVPy/linux/LICENSE"
        "$<TARGET_FILE_DIR:${PYPROJECT_NAME}>/../../tvpy_module-${Python3_VERSION}/TVPy/libs/LICENSE"
)
add_custom_command(
    TARGET ${PYPROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/TVPy/linux/libstdc++.so.6"
        "$<TARGET_FILE_DIR:${PYPROJECT_NAME}>/../../tvpy_module-${Python3_VERSION}/TVPy/libs/libstdc++.so.6"
        COMMENT "Bundling libstdc++.so"
)
endif()
endif()