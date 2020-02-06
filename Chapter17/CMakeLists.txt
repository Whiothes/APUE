cmake_minimum_required(VERSION 3.11)

make_individual(17fig03 17fig04 17fig05)

add_libthreads(17fig03)

add_library(17fig08 STATIC 17fig08)
add_library(17fig09 STATIC 17fig09)
