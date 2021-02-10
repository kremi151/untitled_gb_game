include(CMakeForceCompiler)
cmake_force_c_compiler(lcc "lcc")

cmake_minimum_required(VERSION 2.6)

project(mk_game C)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wa-l -Wl-m -Wl-j -Wl-yt0")

include_directories(
        "/opt/gbdk/include"
    "include"
    "."
)

file(GLOB_RECURSE SOURCES "src/*.c")

add_executable(mk_game ${SOURCES})
set_target_properties(mk_game PROPERTIES OUTPUT_NAME mk_game.gb)

