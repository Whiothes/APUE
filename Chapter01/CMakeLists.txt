cmake_minimum_required(VERSION 3.11)

aux_source_directory("." objs)

foreach(obj ${objs})
  string(REGEX REPLACE "(\./|\.c)" "" file ${obj})
  message("check file: " ${file})
  add_executable(${file} ${obj})
endforeach(obj)
