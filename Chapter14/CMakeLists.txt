cmake_minimum_required(VERSION 3.11)


make_individual(fig14.1 fig14.7 fig14.12 fig14.20 fig14.21 fig14.27
  ex14.1 ex14.5 ex14.7 ex14.8 ex14.11)

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
  target_link_libraries(fig14.21 rt)
endif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
