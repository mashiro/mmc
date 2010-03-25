set(NAME mmc)

include_directories(server)
add_subdirectory(server)

file(GLOB MMC_SOURCES *.cpp *.hpp)
add_executable(${NAME} ${MMC_SOURCES})
target_link_libraries(${NAME} mmc_server)
target_link_libraries(${NAME} ${Boost_LIBRARIES})
