add_library(fig13.1 STATIC fig13.1)

add_library(fig13.6 STATIC fig13.6)
target_link_libraries(fig13.6 apue)


add_executable(fig13.7 fig13.7 fig13.1 fig13.6)
add_executable(fig13.8 fig13.8 fig13.1 fig13.6)

linkThreads(fig13.7 fig13.8)

add_executable(ex13.1 ex13.1)
add_executable(ex13.4 ex13.4)
