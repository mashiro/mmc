cmake_minimum_required(VERSION 2.6)
project(mmc)

find_package(Boost)

include_directories(src)
add_subdirectory(src)

add_executable(mmc main.cpp)
target_link_libraries(mmc mmc_server)
target_link_libraries(mmc boost_program_options)
