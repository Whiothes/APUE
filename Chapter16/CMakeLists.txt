cmake_minimum_required(VERSION 3.11)

# ADD_EXECUTABLE(write write.c)
# ADD_EXECUTABLE(mcopy2 mcopy2.c)
# ADD_EXECUTABLE(deadlock deadlock.c)
# ADD_EXECUTABLE(mandatory mandatory.c)
# ADD_EXECUTABLE(setbuf setbuf.c)

make_individual(16fig09 16fig19)
add_executable(16fig16 16fig16 16fig11)
add_executable(16fig17 16fig17 16fig12)
add_executable(16fig18 16fig18 16fig12)
add_executable(16fig20 16fig20 16fig12)

add_library(16fig22 STATIC 16fig22)
