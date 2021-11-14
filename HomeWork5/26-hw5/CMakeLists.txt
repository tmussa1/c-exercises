cmake_minimum_required(VERSION 3.20)
project(HomeWork5 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(HomeWork5
        fl.c
        fl.h
        process.c
        process_record.c
        mail_merge.c
        wordstore13.c
        ws13.h)
