cmake_minimum_required(VERSION 2.6)
project(mmc)

if (WIN32)
	add_definitions(-D_WIN32_WINNT=0x0501)
endif (WIN32)

find_package(Boost)

add_subdirectory(root)
