make_individual(11fig02 11fig03 11fig04 11fig05 ex11.1 ex11.5)

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
  make_individual(11fig16)
endif()
add_libthreads(11fig02 11fig03 11fig04 11fig05 11fig16 ex11.1 ex11.5)
