cmake_minimum_required(VERSION 2.8)

project(snowhouse)

include_directories("${PROJECT_SOURCE_DIR}")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./bin)

IF(NOT MSVC)

set(CMAKE_CXX_FLAGS "-Wfatal-errors -Wall -W -Werror -Wfloat-equal -Wundef -Wendif-labels -Wshadow -pedantic-errors")

if(${cfg} STREQUAL "C++11") 
  if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "4.7")
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
    else()
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    endif()
  endif()

  if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
  endif()

  if (CMAKE_HOST_APPLE AND (CMAKE_CXX_COMPILER_ID STREQUAL "Clang"))
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
  endif()
endif()
ENDIF()

message(${CMAKE_CXX_FLAGS})

FILE(GLOB SnowhouseSpecSourceFiles example/*.cpp)
add_executable(snowhouse-tests ${SnowhouseSpecSourceFiles})

add_custom_command(TARGET snowhouse-tests
                   POST_BUILD
                   COMMAND snowhouse-tests
                   WORKING_DIRECTORY ./bin)
