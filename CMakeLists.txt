cmake_minimum_required(VERSION 3.15)
project(gumo_engine VERSION 1.0 DESCRIPTION "Game Engine" LANGUAGES C)

add_definitions(-DGM_PLATFORM_WINDOWS)
add_definitions(-DGM_BUILD_DLL)

add_definitions(-DGM_DEBUG)

#--------------------------------------------------------------------
# SET VARIABLES
#--------------------------------------------------------------------
set(CONFIGURATION "DEBUG")
set(PLATFORM "x32")

# DEPENDENCIES DIRECTORIES
set(DEPS_ROOT_DIR "${CMAKE_SOURCE_DIR}/deps")
set(DEPS_INCLUDE_DIR "${DEPS_ROOT_DIR}/include")
set(DEPS_BINARIES_DIR "${DEPS_ROOT_DIR}/bin/${PLATFORM}")
set(DEPS_LIBRARIES_DIR "${DEPS_ROOT_DIR}/lib/${PLATFORM}")

# ENGINE DIRECTORIES
set(GUMO_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(GUMO_INCLUDE_DIR "${GUMO_ROOT_DIR}/include/gumo")
set(GUMO_SOURCE_DIR "${GUMO_ROOT_DIR}/source")

set(GUMO_SOURCE_FILES
        ${GUMO_INCLUDE_DIR}/renderer/renderer.h
        ${GUMO_INCLUDE_DIR}/renderer/shader.h
        ${GUMO_INCLUDE_DIR}/renderer/buffer.h
        ${GUMO_INCLUDE_DIR}/renderer/vertex_array.h
        ${GUMO_INCLUDE_DIR}/renderer/camera.h
        ${GUMO_INCLUDE_DIR}/renderer/texture.h
        ${GUMO_INCLUDE_DIR}/application.h
        ${GUMO_INCLUDE_DIR}/core.h
        ${GUMO_INCLUDE_DIR}/math.h
        ${GUMO_INCLUDE_DIR}/input.h
        ${GUMO_INCLUDE_DIR}/entry_point.h
        ${GUMO_INCLUDE_DIR}/window.h
        ${GUMO_INCLUDE_DIR}/logger.h
        ${GUMO_INCLUDE_DIR}/resource_manager.h source/resource_manager.c)

add_subdirectory(${GUMO_SOURCE_DIR})
add_library(gumo_engine ${GUMO_SOURCE_FILES})

target_include_directories(gumo_engine PUBLIC $<BUILD_INTERFACE:${DEPS_INCLUDE_DIR}>)
target_include_directories(gumo_engine PRIVATE $<BUILD_INTERFACE:${DEPS_BINARIES_DIR}>)
target_include_directories(gumo_engine PUBLIC $<BUILD_INTERFACE:${GUMO_ROOT_DIR}/include>)
target_include_directories(gumo_engine PRIVATE $<BUILD_INTERFACE:${GUMO_SOURCE_DIR}>)

target_link_directories(gumo_engine PUBLIC ${DEPS_LIBRARIES_DIR})
target_link_libraries(gumo_engine opengl32 glfw3dll glew32)

add_subdirectory(examples/sandbox)