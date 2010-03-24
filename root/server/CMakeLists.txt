set(NAME mmc_server)

add_subdirectory(command)

file(GLOB MMC_SERVER_SOURCES *.cpp *.hpp)
add_library(${NAME} STATIC ${MMC_SERVER_SOURCES})
target_link_libraries(${NAME} mmc_command)
if (NOT WIN32)
	target_link_libraries(${NAME} boost_system-mt)
	target_link_libraries(${NAME} boost_thread-mt)
endif (NOT WIN32)
