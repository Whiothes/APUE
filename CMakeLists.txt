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

message(STATUS "The CMAKE_SYSTEM_NAME: " ${CMAKE_SYSTEM_NAME})
if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
  find_package(Threads)
  add_definitions(-D_POSIX_C_SOURCE=200809L)
endif()

link_libraries(apue)
link_directories("${PROJECT_SOURCE_DIR}/lib")

# define a functon for loop
function(add_libthreads)
  if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    foreach(file ${ARGN})
      target_link_libraries(${file} ${CMAKE_THREAD_LIBS_INIT} pthread)
    endforeach()
  endif()
endfunction()

function(make_individual)
  foreach(file ${ARGN})
    string(REGEX REPLACE "(\./|\.c)" "" file ${file})
    message("check file: " ${file})
    add_executable(${file} ${file})
  endforeach(file)
endfunction(make_individual)



add_subdirectory("Chapter01")
# add_subdirectory("Chapter02")
# add_subdirectory("Chapter07")
add_subdirectory("Chapter08")
add_subdirectory("Chapter09")
add_subdirectory("Chapter10")
add_subdirectory("Chapter11")
add_subdirectory("Chapter12")
add_subdirectory("Chapter13")
add_subdirectory("Chapter14")
# add_subdirectory("Chapter15")
