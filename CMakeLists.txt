set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_LIST_DIR}/GBDK.cmake)

cmake_minimum_required(VERSION 2.9)

project(mk_game C)

file(GLOB_RECURSE SOURCES "src/*.c")

add_executable(mk_game ${SOURCES})

target_include_directories(mk_game PRIVATE ${GBDK_INCLUDE_DIR})

# 0x10 : MBC3+TIMER+RAM+BATTERY
# 2 ROM banks (minimum)
# 4 RAM banks (default for MBC3)
add_gb_rom(mk_game 0x10 2 4)
