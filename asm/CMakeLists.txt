cmake_minimum_required(VERSION 2.4)

project(asm)

include_directories(src)

add_executable(asm main.c instruction_set.h asm.c asm.h context.c context.h)