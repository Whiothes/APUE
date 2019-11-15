add_executable(fig12.8 fig12.8 fig12.4)

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
  target_link_libraries(fig12.8 ${CMAKE_THREAD_LIBS_INIT} pthread)
endif()
