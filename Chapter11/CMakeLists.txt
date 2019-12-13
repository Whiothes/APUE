make_individual(fig11.2 fig11.3 fig11.4 fig11.5 ex11.1 ex11.5)

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
  make_individual(fig11.16)
endif()
add_libthreads(fig11.2 fig11.3 fig11.4 fig11.5 fig11.16 ex11.1 ex11.5)
