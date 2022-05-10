cmake_minimum_required(VERSION 2.4)

project(virstack)

include_directories(${PROJECT_SOURCE_DIR}/src)

add_executable(app src/main.c
        src/config.h
        src/vm.c
        src/vm.h
        src/util.h src/instruction_set.h src/vistack.h src/virstack.c)
