cmake_minimum_required(VERSION 2.8)

project(snowhouse)

option(SNOWHOUSE_BUILD_TESTS    "Build the Snowhouse tests"                 OFF)
option(SNOWHOUSE_RUN_TESTS      "Run the Snowhouse tests"                   OFF)
set(SNOWHOUSE_CXX_STANDARD "C++11" CACHE STRING "The C++ standard the examples are compiled with")
set_property(CACHE SNOWHOUSE_CXX_STANDARD PROPERTY STRINGS "C++11" "C++14" "C++17")

if (NOT ${CMAKE_VERSION} VERSION_LESS "3.0.0")
    add_library(snowhouse INTERFACE)
    target_include_directories(snowhouse INTERFACE include)
endif()

if(SNOWHOUSE_CXX_STANDARD STREQUAL "C++11")
  set(std_name "c++11")
elseif(SNOWHOUSE_CXX_STANDARD STREQUAL "C++14")
  set(std_name "c++14")
elseif(SNOWHOUSE_CXX_STANDARD STREQUAL "C++17")
  set(std_name "c++17")
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
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} \
    -Wall -Wextra -pedantic -Wdeprecated -Wdeprecated-declarations -Wnon-virtual-dtor \
    -Wshadow -Wfloat-equal -Wundef -Wendif-labels -Wno-error=unknown-pragmas")

  if(DEFINED std_name)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=${std_name}")
  endif()
endif()

message(STATUS "C++ compiler flags: ${CMAKE_CXX_FLAGS}")

if (SNOWHOUSE_BUILD_TESTS)
    FILE(GLOB SnowhouseSpecSourceFiles example/*.cpp)
    add_executable(snowhouse-tests ${SnowhouseSpecSourceFiles})
    if (NOT ${CMAKE_VERSION} VERSION_LESS "3.0.0")
        target_link_libraries(snowhouse-tests PRIVATE snowhouse)
    else()
        include_directories("${PROJECT_SOURCE_DIR}/include")
    endif()
endif()

if (SNOWHOUSE_BUILD_TESTS AND SNOWHOUSE_RUN_TESTS)
    add_custom_command(TARGET snowhouse-tests
                       POST_BUILD
                       COMMAND snowhouse-tests
                       WORKING_DIRECTORY ./bin)
elseif (SNOWHOUSE_RUN_TESTS)
    message(WARNING "Unable to run snowhouse tests - set:\n  option(SNOWHOUSE_BUILD_TESTS, \"Build the Snowhouse tests\" ON)\nand clear your CMakeCache.txt")
endif()
