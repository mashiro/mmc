cmake_minimum_required(VERSION 2.6)
project(mmc)

if (WIN32)
	add_definitions(-D_WIN32_WINNT=0x0501)
endif (WIN32)

# find boost
find_package(Boost)
if (Boost_FOUND)
	include_directories(${BOOST_INCLUDE_DIR})
	link_directories(${BOOST_LIBRARY_DIRS})
else (Boost_FOUND)
    message(FATAL_ERROR "Boost not found")
endif (Boost_FOUND)

add_subdirectory(root)
