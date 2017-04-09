cmake_minimum_required(VERSION 2.8)

project(snowhouse)

option(SNOWHOUSE_BUILD_TESTS    "Build the Snowhouse tests"                 ON)
option(SNOWHOUSE_RUN_TESTS      "Run the Snowhouse tests"                   ON)
set(SNOWHOUSE_CXX_STANDARD "C++03" CACHE STRING "The C++ standard the examples are compiled with")
set_property(CACHE SNOWHOUSE_CXX_STANDARD PROPERTY STRINGS "C++98" "C++03" "C++11" "C++14")

include_directories("${PROJECT_SOURCE_DIR}")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./bin)

if (MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /MP ")
else()
  # Assume GCC-style arguments
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wfatal-errors -Wall -W -Werror -Wfloat-equal -Wundef -Wendif-labels -Wshadow -pedantic-errors")
  if(SNOWHOUSE_CXX_STANDARD STREQUAL "C++11" OR SNOWHOUSE_CXX_STANDARD STREQUAL "C++14")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wdeprecated")
  endif()

  if(SNOWHOUSE_CXX_STANDARD STREQUAL "C++98")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++98")
  elseif(SNOWHOUSE_CXX_STANDARD STREQUAL "C++03")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++03")
  elseif(SNOWHOUSE_CXX_STANDARD STREQUAL "C++11")
    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS "4.7")
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
    else()
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    endif()

    if (CMAKE_HOST_APPLE AND (CMAKE_CXX_COMPILER_ID STREQUAL "Clang"))
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
    endif()
  elseif(SNOWHOUSE_CXX_STANDARD STREQUAL "C++14")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
  endif()
endif()

message(STATUS "C++ compiler flags: ${CMAKE_CXX_FLAGS}")

if (SNOWHOUSE_BUILD_TESTS)
    FILE(GLOB SnowhouseSpecSourceFiles example/*.cpp)
    add_executable(snowhouse-tests ${SnowhouseSpecSourceFiles})
endif()

if (SNOWHOUSE_BUILD_TESTS AND SNOWHOUSE_RUN_TESTS)
    add_custom_command(TARGET snowhouse-tests
                       POST_BUILD
                       COMMAND snowhouse-tests
                       WORKING_DIRECTORY ./bin)
elseif (SNOWHOUSE_RUN_TESTS)
    message(WARNING "Unable to run snowhouse tests - set:\n  option(SNOWHOUSE_BUILD_TESTS, \"Build the Snowhouse tests\" ON)\nand clear your CMakeCache.txt")
endif()
