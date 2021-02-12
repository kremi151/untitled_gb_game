# Use Linux to omit any unwanted file extension in the created ROM file
set(CMAKE_SYSTEM_NAME Generic)

if ("${GBDK_ROOT}" STREQUAL "")
    message(FATAL_ERROR "No GBDK_ROOT path defined")
endif()

set(CMAKE_C_COMPILER lcc)
set(CMAKE_C_COMPILER_FORCED TRUE)

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
    set(GB_MBC_TYPE 0)
    if(ARGC GREATER_EQUAL 2)
        set(GB_MBC_TYPE ${ARGV1})
    endif()
    set(GB_ROM_BANKS 2)
    if(ARGC GREATER_EQUAL 3)
        set(GB_ROM_BANKS ${ARGV2})
    endif()
    set(GB_RAM_BANKS 0)
    if(ARGC GREATER_EQUAL 4)
        set(GB_RAM_BANKS ${ARGV3})
    endif()


    set_target_properties(${target} PROPERTIES OUTPUT_NAME ${target} SUFFIX ".gb")
    target_compile_options(${target} PRIVATE -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG)
    target_link_options(${target} PRIVATE "-Wl-yt${GB_MBC_TYPE}" "-Wl-yo${GB_ROM_BANKS}" "-Wl-ya${GB_RAM_BANKS}")
endfunction()
