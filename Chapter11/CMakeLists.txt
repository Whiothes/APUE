add_executable(fig11.2 fig11.2)
add_executable(fig11.3 fig11.3)
add_executable(fig11.4 fig11.4)
add_executable(fig11.5 fig11.5)

add_executable(ex11.1 ex11.1)
add_executable(ex11.5 ex11.5)

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
  add_executable(fig11.16 fig11.16)
endif()
linkThreads(fig11.2 fig11.3 fig11.4 fig11.5 fig11.16 ex11.1 ex11.5)
