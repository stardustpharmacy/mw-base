cmake_minimum_required(VERSION 3.10)
project(bot C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# gives error with older compilers, disable dependency tracking
set(CMAKE_DISABLE_DEPENDENCY_TRACKING TRUE)
set(CMAKE_C_LINKER_DEPFILE_FLAGS "")

# stolen from Mirai
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -fomit-frame-pointer -fdata-sections -ffunction-sections -std=c99 -static")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--gc-sections")

# src & inc dirs
set(SRC_DIR src)
set(INC_DIR include)

include_directories(${INC_DIR})
file(GLOB_RECURSE SRC_FILES "${SRC_DIR}/*.c")
file(GLOB_RECURSE HDR_FILES "${INC_DIR}/*.h")
add_executable(bot ${SRC_FILES} ${HDR_FILES})

# eee
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DBOT_DEBUG)
endif ()
