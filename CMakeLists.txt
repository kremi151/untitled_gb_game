# GB TOOLCHAIN START
if ("${GBDK_ROOT}" STREQUAL "")
    message(FATAL_ERROR "No GBDK_ROOT path defined")
endif()
set(CMAKE_C_COMPILER lcc)
set(CMAKE_C_COMPILER_FORCED TRUE)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wa-l -Wl-m -Wl-j -Wl-yt0")
set(CMAKE_PROGRAM_PATH ${GBDK_ROOT}/bin)
set(CMAKE_INCLUDE_PATH ${GBDK_ROOT}/include)
set(CMAKE_LIBRARY_PATH ${GBDK_ROOT}/lib)
set(GBDK_INCLUDE_DIR ${GBDK_ROOT}/include)
# GB TOOLCHAIN END

cmake_minimum_required(VERSION 2.6)

project(mk_game C)

file(GLOB_RECURSE SOURCES "src/*.c")

add_executable(mk_game ${SOURCES})

target_include_directories(mk_game PRIVATE ${GBDK_INCLUDE_DIR})

set_target_properties(mk_game PROPERTIES OUTPUT_NAME mk_game.gb)
