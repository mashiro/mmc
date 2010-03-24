set(NAME mmc)

include_directories(server)
add_subdirectory(server)

file(GLOB MMC_SOURCES *.cpp *.hpp)
add_executable(${NAME} ${MMC_SOURCES})
target_link_libraries(${NAME} mmc_server)
if (NOT WIN32)
	target_link_libraries(${NAME} boost_program_options-mt)
endif (NOT WIN32)
