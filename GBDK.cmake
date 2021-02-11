# Use Linux to omit any unwanted file extension in the created ROM file
set(CMAKE_SYSTEM_NAME Linux)

if ("${GBDK_ROOT}" STREQUAL "")
    message(FATAL_ERROR "No GBDK_ROOT path defined")
endif()

set(CMAKE_C_COMPILER lcc)
set(CMAKE_C_COMPILER_FORCED TRUE)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wa-l -Wl-m -Wl-j -Wl-yt0")

set(GBDK_INCLUDE_DIR ${GBDK_ROOT}/include)
set(GBDK_LIB_DIR ${GBDK_ROOT}/lib)

set(CMAKE_PROGRAM_PATH ${GBDK_ROOT}/bin)
set(CMAKE_INCLUDE_PATH ${GBDK_INCLUDE_DIR})
set(CMAKE_LIBRARY_PATH ${GBDK_LIB_DIR})


set(CMAKE_SYSTEM_INCLUDE_PATH ${GBDK_INCLUDE_DIR})
set(CMAKE_SYSTEM_LIBRARY_PATH  ${GBDK_LIB_DIR})

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

set_property(GLOBAL PROPERTY TARGET_SUPPORTS_SHARED_LIBS FALSE)

function(add_gb_rom target)
    set_target_properties(${target} PROPERTIES OUTPUT_NAME "${target}.gb")
endfunction()