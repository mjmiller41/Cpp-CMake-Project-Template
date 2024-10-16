 cmake_minimum_required(VERSION 3.30)

project(OdfReader VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(PROJECT_SOURCE_DIR src)

set(RAPIDXML_ROOT libs/rapidxml-1.13)
set(BIT7Z_ROOT libs/bit7z)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_DEBUG} -g -O2 -DNDEBUG")

include_directories(${RAPIDXML_ROOT})
add_subdirectory(${BIT7Z_ROOT})

add_executable(OdfReader
  src/main.cpp
)

target_link_libraries(OdfReader PRIVATE bit7z)
