if (WIN32)
	add_definitions(-D_WIN32_WINNT=0x0501)
endif (WIN32)

add_subdirectory(command)

file(GLOB MMC_SOURCES *.cpp)
add_library(mmc_server STATIC ${MMC_SOURCES})
target_link_libraries(mmc_server mmc_command)
target_link_libraries(mmc_server boost_system)
target_link_libraries(mmc_server boost_thread-mt)
