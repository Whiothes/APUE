cmake_minimum_required(VERSION 3.11)


make_individual(14fig01 14fig07 14fig12 14fig20 14fig21 14fig27
  14ex01 14ex05 14ex07 14ex08 14ex11)

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
  target_link_libraries(14ex08 rt)
  target_link_libraries(14fig21 rt)
endif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
