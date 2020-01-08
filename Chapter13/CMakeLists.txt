add_library(13fig01 STATIC 13fig01)

add_library(13fig06 STATIC 13fig06)
target_link_libraries(13fig06 apue)


add_executable(13fig07 13fig07 13fig01 13fig06)
add_executable(13fig08 13fig08 13fig01 13fig06)

add_libthreads(13fig07 13fig08)

add_executable(ex13.1 ex13.1)
add_executable(ex13.4 ex13.4)
