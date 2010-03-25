cmake_minimum_required(VERSION 2.6)
project(mmc)

if (WIN32)
	add_definitions(-D_WIN32_WINNT=0x0501)
endif (WIN32)

# boost
set(Boost_USE_MULTITHREADED ON)
find_package(Boost COMPONENTS program_options thread system)
if(Boost_FOUND)
	include_directories(${Boost_INCLUDE_DIRS})
	link_directories(${Boost_LIBRARY_DIRS})
else()
    message(FATAL_ERROR "Boost not found")
endif()

add_subdirectory(root)
