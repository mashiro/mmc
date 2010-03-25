cmake_minimum_required(VERSION 2.6)
project(mmc)

# boost
if(WIN32)
	set(Boost_USE_STATIC_LIBS ON)
	add_definitions(-D_WIN32_WINNT=0x0501)
	add_definitions(${Boost_LIB_DIAGNOSTIC_DEFINTIIONS})
endif()
set(Boost_USE_MULTITHREADED ON)
find_package(Boost COMPONENTS program_options thread system)
if(Boost_FOUND)
	include_directories(${Boost_INCLUDE_DIRS})
	link_directories(${Boost_LIBRARY_DIRS})
endif()

add_subdirectory(root)
