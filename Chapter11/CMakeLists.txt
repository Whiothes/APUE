add_executable(fig11.2 fig11.2)
add_executable(fig11.3 fig11.3)
add_executable(fig11.4 fig11.4)
add_executable(fig11.5 fig11.5)
add_executable(fig11.16 fig11.16)

add_executable(ex11.1 ex11.1)

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
  find_package(Threads)
  target_link_libraries(fig11.2 ${CMAKE_THREAD_LIBS_INIT})
  target_link_libraries(fig11.3 ${CMAKE_THREAD_LIBS_INIT})
  target_link_libraries(fig11.4 ${CMAKE_THREAD_LIBS_INIT})
  target_link_libraries(fig11.5 ${CMAKE_THREAD_LIBS_INIT})
  target_link_libraries(fig11.16 ${CMAKE_THREAD_LIBS_INIT})

  target_link_libraries(ex11.1 ${CMAKE_THREAD_LIBS_INIT})
endif()
