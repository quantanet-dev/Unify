cmake_minimum_required(VERSION 3.31.0)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(
    UNIFY
    VERSION 0.1.0
    DESCRIPTION "Unify Engine"
    LANGUAGES CXX
)

file(GLOB_RECURSE UNIFY_SRCS ${CMAKE_SOURCE_DIR}/Unify/src/**.cpp)
file(GLOB_RECURSE EDITOR_SRCS ${CMAKE_SOURCE_DIR}/Editor/src/**.cpp)

set(
    ${UNIFY_INLCUDES}
    ${CMAKE_SOURCE_DIR}/Unify/include
    ${CMAKE_SOURCE_DIR}/Unify/vendor/**/include
)

set(
    ${EDITOR_INLCUDES}
    ${UNIFY_INCLUDES}
    ${CMAKE_SOURCE_DIR}/Editor/include
)

add_library(
    UNIFY
    SHARED
    ${UNIFY_SRCS}
)

target_include_directories(
    UNIFY
    PRIVATE
    ${UNIFY_INCLUDES}
)

add_executable(
    EDITOR
    ${EDITOR_SRCS}
)

target_include_directories(
    EDITOR
    PRIVATE
    ${EDITOR_INLCUDES}
)

target_link_libraries(
    EDITOR
    UNIFY
)