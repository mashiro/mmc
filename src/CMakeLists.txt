file(GLOB mmc_SOURCES *.cpp)
add_executable(mmc ${mmc_SOURCES})
target_link_libraries(mmc boost_system)
target_link_libraries(mmc boost_thread)
