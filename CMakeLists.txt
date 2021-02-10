# GB TOOLCHAIN START
include(CMakeForceCompiler)
set(CMAKE_PROGRAM_PATH /opt/gbdk/bin)
set(CMAKE_INCLUDE_PATH /opt/gbdk/include)
set(CMAKE_LIBRARY_PATH /opt/gbdk/lib)
cmake_force_c_compiler(lcc "lcc")
# GB TOOLCHAIN END

cmake_minimum_required(VERSION 2.6)

project(mk_game C)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wa-l -Wl-m -Wl-j -Wl-yt0")

include_directories(
    "include"
    "."
)

file(GLOB_RECURSE SOURCES "src/*.c")

add_executable(mk_game ${SOURCES})
set_target_properties(mk_game PROPERTIES OUTPUT_NAME mk_game.gb)

