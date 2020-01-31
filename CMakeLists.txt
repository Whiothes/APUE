cmake_minimum_required(VERSION 3.5.1)

# definition options
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -std=gnu11")
if (APPLE)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D_DARWIN_C_SOURCE")
elseif(UNIX)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D_POSIX_C_SOURCE=200809L -D_GNU_SOURCE")
endif()

set(CMAKE_VERBOSE_MAKEFILE ON)

project(APUE)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

SET(PROJECT_SOURCE_DIR      ${CMAKE_CURRENT_SOURCE_DIR})
SET(EXECUTABLE_OUTPUT_PATH  ${PROJECT_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH     ${PROJECT_SOURCE_DIR}/lib)

include_directories("${PROJECT_SOURCE_DIR}/include")
aux_source_directory("${PROJECT_SOURCE_DIR}/lib" libapue)
add_library(apue STATIC ${libapue})


link_libraries(apue)
link_directories("${PROJECT_SOURCE_DIR}/lib")

# define a functon for loop
function(add_libthreads)
  if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    find_package(Threads)
    foreach(file ${ARGN})
      target_link_libraries(${file} Threads::Threads)
    endforeach()
  endif()
endfunction()

function(make_individual)
  foreach(file ${ARGN})
    string(REGEX REPLACE "(\./|\.c)" "" file ${file})
    message("check file: " ${file})
    add_executable("${file}" "${file}")
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
add_subdirectory("Chapter15")
add_subdirectory("Chapter16")
