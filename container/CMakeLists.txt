cmake_minimum_required(VERSION 2.4)

project(test_lib)

add_library(Container
        array.h
        array.c
        arraylist.h
        arraylist.c
        hashmap.h
        hashmap.c
        linkedlist.h
        linkedlist.c
        container.h iteraror.h)

add_executable(test main.c hashmap.h hashmap.c array.c array.h arraylist.c arraylist.h linkedlist.c linkedlist.h iteraror.h)