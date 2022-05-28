cmake_minimum_required(VERSION 2.4)

project(vasm)

include_directories(src)

add_executable(vasm main.c instruction_set.h asm.c asm.h context.c context.h output.c output.h)