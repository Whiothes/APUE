cmake_minimum_required(VERSION 3.11)


make_individual(14fig01 14fig07 14fig12 14fig20 14fig21 14fig27
  ex14.1 ex14.5 ex14.7 ex14.8 ex14.11)

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
  target_link_libraries(ex14.8 rt)
  target_link_libraries(14fig21 rt)
endif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
