aux_source_directory("." objs)

foreach(obj ${objs})
  string(REPLACE "./" "" file ${obj})
  add_executable(${file} ${file})
  target_link_libraries(${file} apue)
endforeach(obj)
