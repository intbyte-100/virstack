cmake_minimum_required(VERSION 2.4)

project(virstack C ASM_NASM)



include_directories(src)

add_executable(virstack src/main.c
        src/interpreter.asm
        src/interpreter.h
        src/config.h
        src/vm.c
        src/vm.h
        src/util.h src/instruction_set.h src/vistack.h src/virstack.c src/loader.c src/loader.h src/scope.h src/scope.c src/debug.c src/debug.h)
