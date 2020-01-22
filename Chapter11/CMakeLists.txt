make_individual(11fig02 11fig03 11fig04 11fig05 11ex01 11ex05)

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
  make_individual(11fig16)
endif()
add_libthreads(11fig02 11fig03 11fig04 11fig05 11fig16 11ex01 11ex05)
