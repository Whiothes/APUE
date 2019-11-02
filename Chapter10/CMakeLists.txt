add_executable(fig10.2 fig10.2)
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
add_executable(fig10.23 fig10.23)
add_executable(fig10.26 fig10.26 fig10.28)
add_executable(fig10.31 fig10.31)

add_executable(ex10.6 ex10.6)
add_executable(ex10.9 ex10.9)
add_executable(ex10.10 ex10.10)

add_executable(ex10.11 fig10.19 ex10.11)
add_executable(ex10.12 ex10.12)
