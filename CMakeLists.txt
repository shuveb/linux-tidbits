cmake_minimum_required(VERSION 3.16)
project(linux_tidbits C)

set(CMAKE_C_STANDARD 99)

add_executable(gen_nums 02_process_group_signals/gen_nums.c)
add_executable(add_nums 02_process_group_signals/add_nums.c)
