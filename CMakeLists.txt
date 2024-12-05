cmake_minimum_required(VERSION 3.31.0)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS)

project(
    Unify
    VERSION 0.1.0
    DESCRIPTION "Unify Engine w/ Unify Editor"
    LANGUAGES CXX
)

set(CMAKE_SHARED_LIBRARY_PREFIX "")
set(CMAKE_STATIC_LIBRARY_PREFIX "")

file(GLOB_RECURSE UNIFY_SRCS ${CMAKE_SOURCE_DIR}/Unify/src/**.cpp)
file(GLOB_RECURSE EDITOR_SRCS ${CMAKE_SOURCE_DIR}/Editor/src/**.cpp)

add_subdirectory(${CMAKE_SOURCE_DIR}/Unify/vendor/spdlog)
add_subdirectory(${CMAKE_SOURCE_DIR}/Unify/vendor/glfw)

add_library(
    UnifyEngine
    SHARED
    ${UNIFY_SRCS}
)

target_precompile_headers(UnifyEngine PRIVATE ${CMAKE_SOURCE_DIR}/Unify/unpch.h)

target_include_directories(
    UnifyEngine
    PRIVATE
    ${CMAKE_SOURCE_DIR}/Unify
    ${CMAKE_SOURCE_DIR}/Unify/include
)

target_link_libraries(
    UnifyEngine
    spdlog::spdlog
    glfw
)

add_executable(
    UnifyEditor
    ${EDITOR_SRCS}
)

# target_precompile_headers(EDITOR REUSE_FROM UNIFY)

target_include_directories(
    UnifyEditor
    PRIVATE
    ${CMAKE_SOURCE_DIR}/Unify
    ${CMAKE_SOURCE_DIR}/Editor/include
    ${CMAKE_SOURCE_DIR}/Unify/include
)

target_link_libraries(
    UnifyEditor
    UnifyEngine
)