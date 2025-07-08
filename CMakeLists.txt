cmake_minimum_required(VERSION 3.10)

project(stargate)

# C++ standard
set(CXX_STANDARD 20)
set(CPP_STANDARD "-std=c++${CXX_STANDARD}")

# C++ warning flags
set(CPP_WARNINGS "-Wall -Werror -Wunused-function -Wunused-variable")

# Detect debug build
set(DEBUG_BUILD FALSE)
if (DEFINED ENV{DEBUG_BUILD})
    if ($ENV{DEBUG_BUILD} EQUAL "1")
        set(DEBUG_BUILD TRUE)
    endif()
endif()

# Detect RELDEBUG
set(RELDEBUG FALSE)
if (DEFINED ENV{RELDEBUG})
    if ($ENV{RELDEBUG} EQUAL "1")
        set(RELDEBUG TRUE)
    endif()
endif()

# Detect CALLGRIND_PROFILE
set(CALLGRIND_PROFILE FALSE)
if (DEFINED ENV{CALLGRIND_PROFILE})
    if ($ENV{CALLGRIND_PROFILE} EQUAL "1")
        set(CALLGRIND_PROFILE TRUE)
    endif()
endif()

if(${CALLGRIND_PROFILE})
    if (NOT ${DEBUG_BUILD})
        set(RELDEBUG TRUE)
    endif()
    add_definitions(-DCALLGRIND_PROFILE)
endif()

# Debug settings
if (${DEBUG_BUILD})
    message(STATUS "Debug build")
    set(OPTIMIZE_FLAGS "-O0 -g -fcf-protection=none")
else()
    message(STATUS "Optimized build")
    add_definitions(-DNDEBUG)
    set(OPTIMIZE_FLAGS "-O3 -fcf-protection=none")

    if (${RELDEBUG})
        set(OPTIMIZE_FLAGS "${OPTIMIZE_FLAGS} -g")
    endif()
endif()

# C++ flags
set(CMAKE_CXX_FLAGS "${CPP_STANDARD} ${CPP_WARNINGS} ${OPTIMIZE_FLAGS}")

# Create compilation database and symlink in the src folder
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
execute_process(
    COMMAND ${CMAKE_COMMAND} -E create_symlink
        ${CMAKE_BINARY_DIR}/compile_commands.json
        ${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json
)

# Threads
find_package(Threads REQUIRED)

# Detect Homebrew flex installation
if(CMAKE_HOST_SYSTEM_NAME MATCHES "Darwin")
    execute_process(
        COMMAND brew --prefix flex
        RESULT_VARIABLE BREW_FLEX_RESULT
        OUTPUT_VARIABLE BREW_FLEX_PREFIX
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    if(BREW_FLEX_RESULT EQUAL 0 AND EXISTS "${BREW_FLEX_PREFIX}")
        set(FLEX_EXECUTABLE "${BREW_FLEX_PREFIX}/bin/flex")
        set(CMAKE_PREFIX_PATH "${BREW_FLEX_PREFIX}" ${CMAKE_PREFIX_PATH})
    endif()
endif()

find_package(FLEX REQUIRED)

# Validate FlexLexer.h availability
if(NOT FLEX_INCLUDE_DIRS OR FLEX_INCLUDE_DIRS STREQUAL "FLEX_INCLUDE_DIR-NOTFOUND")
    find_path(FLEX_INCLUDE_DIR FlexLexer.h
        PATHS /usr/local/opt/flex/include
              /opt/homebrew/include
              /usr/local/include
              /usr/include
    )
    if(FLEX_INCLUDE_DIR)
        set(FLEX_INCLUDE_DIRS ${FLEX_INCLUDE_DIR})
    else()
        message(FATAL_ERROR "FlexLexer.h not found. Install flex development headers.")
    endif()
endif()

message(STATUS "FLEX_INCLUDE_DIR ${FLEX_INCLUDE_DIRS}")

add_subdirectory(external)
add_subdirectory(common)
add_subdirectory(nl)
add_subdirectory(tools)
