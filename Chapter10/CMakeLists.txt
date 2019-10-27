add_executable(sigfunc sigfunc)
add_executable(fig10.5 fig10.5)
add_executable(fig10.6 fig10.6)


add_executable(fig10.9 fig10.9)
add_library(sleep SHARED fig10.7 fig10.8)
target_link_libraries(fig10.9 sleep)

add_executable(fig10.10 fig10.10)
add_executable(fig10.11 fig10.11)
add_executable(fig10.15 fig10.15)
add_executable(fig10.20 fig10.20 fig10.14)
add_executable(fig10.22 fig10.22)
