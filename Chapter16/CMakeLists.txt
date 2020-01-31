cmake_minimum_required(VERSION 3.11)

# ADD_EXECUTABLE(write write.c)
# ADD_EXECUTABLE(mcopy2 mcopy2.c)
# ADD_EXECUTABLE(deadlock deadlock.c)
# ADD_EXECUTABLE(mandatory mandatory.c)
# ADD_EXECUTABLE(setbuf setbuf.c)

make_individual(16fig09 16fig19 16ex01 16ex02 16ex04s )
add_executable(16fig16 16fig16 16fig11)
add_executable(16fig17 16fig17 16fig12)
add_executable(16fig18 16fig18 16fig12)
add_executable(16fig20 16fig20 16fig12)
add_executable(16ex03 16ex03 16fig12)
add_executable(16ex04c 16ex04c)
add_executable(16ex05 16ex05 16fig12)

add_library(16fig22 STATIC 16fig22)
add_library(16ex06 STATIC 16ex06)
