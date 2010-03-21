add_subdirectory(command)

file(GLOB MMC_SOURCES *.cpp)
add_library(mmc_server STATIC ${MMC_SOURCES})
target_link_libraries(mmc_server mmc_command)
if (NOT WIN32)
	target_link_libraries(mmc_server boost_system-mt)
	target_link_libraries(mmc_server boost_thread-mt)
endif (NOT WIN32)
