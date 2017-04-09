cmake_minimum_required(VERSION 2.8)

project(snowhouse)

option(SNOWHOUSE_BUILD_TESTS    "Build the Snowhouse tests"                 ON)
option(SNOWHOUSE_RUN_TESTS      "Run the Snowhouse tests"                   ON)
set(SNOWHOUSE_CXX_STANDARD "C++03" CACHE STRING "The C++ standard the examples are compiled with")
set_property(CACHE SNOWHOUSE_CXX_STANDARD PROPERTY STRINGS "C++98" "C++03" "C++11" "C++14")

include_directories("${PROJECT_SOURCE_DIR}")

if(SNOWHOUSE_CXX_STANDARD STREQUAL "C++98")
  set(std_name "c++98")
elseif(SNOWHOUSE_CXX_STANDARD STREQUAL "C++03")
  set(std_name "c++03")
elseif(SNOWHOUSE_CXX_STANDARD STREQUAL "C++11")
  set(std_name "c++11")
elseif(SNOWHOUSE_CXX_STANDARD STREQUAL "C++14")
  set(std_name "c++14")
else()
  message(WARNING "C++ standard \"${SNOWHOUSE_CXX_STANDARD}\" not known, falling back to default")
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./bin)

if (MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /MP ")
  if(DEFINED std_name)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:${std_name}")
  endif()
else()
  # Assume GCC-style arguments
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wfatal-errors -Wall -W -Werror -Wfloat-equal -Wundef -Wendif-labels -Wshadow -pedantic-errors")
  if(SNOWHOUSE_CXX_STANDARD STREQUAL "C++11" OR SNOWHOUSE_CXX_STANDARD STREQUAL "C++14")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wdeprecated")
  endif()

  if(DEFINED std_name)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=${std_name}")
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
