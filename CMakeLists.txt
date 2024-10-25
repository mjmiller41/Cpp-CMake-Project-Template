cmake_minimum_required(VERSION 3.28)
 
project(OdfReader VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(PROJECT_SOURCE_DIR src)

add_subdirectory(${OdfReader_SOURCE_DIR}/OdfReader)
add_subdirectory(${OdfReader_SOURCE_DIR}/rapidxml-1.13)

include(FetchContent)
FetchContent_Declare(KZip GIT_REPOSITORY https://github.com/troldal/KZip.git)
                         #GIT_TAG 1.11.0) # Replace with your desired git commit from: https://github.com/libcpr/cpr/releases
FetchContent_MakeAvailable(KZip)

target_link_libraries(OdfReader PUBLIC KZip)

