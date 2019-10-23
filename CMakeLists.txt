cmake_minimum_required(VERSION 3.5.1)
add_definitions(-std=c11 -g -D_DARWIN_C_SOURCE)

project(APUE)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

SET(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

include_directories("${PROJECT_SOURCE_DIR}/include")
aux_source_directory("${PROJECT_SOURCE_DIR}/lib" libapue)
add_library(apue STATIC ${libapue})
set_target_properties(apue
  PROPERTIES
  VERSION 1.0
  SOVERSION 1)


link_libraries(apue)
link_directories("${PROJECT_SOURCE_DIR}/lib")

# add_subdirectory("Chapter07")
add_subdirectory("Chapter08")
add_subdirectory("Chapter10")
# add_subdirectory("Chapter15")
