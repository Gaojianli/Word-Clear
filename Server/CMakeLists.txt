CMAKE_MINIMUM_REQUIRED(VERSION 2.8) 

PROJECT(WordGameBackEnd) 

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
SET(CMAKE_BUILD_TYPE "Release")

SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

# set(CMAKE_VERBOSE_MAKEFILE ON)

# enable_testing() 

# add_definitions(-DDEBUG)

SET(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin")

INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/include")

MESSAGE("Identifying the OS...")
if(WIN32)
  MESSAGE("This is Windows.")
elseif(APPLE)
  MESSAGE("This is MacOS.")
elseif(UNIX)
  MESSAGE("This is Linux.")
endif()

AUX_SOURCE_DIRECTORY(src DIR_SRCS)

add_executable(wordGamed
   src/pch.cpp
   ${DIR_SRCS}
)
target_link_libraries(wordGamed uv mysqlclient) 
