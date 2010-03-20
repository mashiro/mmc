file(GLOB MMC_SOURCES *.cpp command/*.cpp)
add_library(mmc2 STATIC ${MMC_SOURCES})
target_link_libraries(mmc2 boost_system)
target_link_libraries(mmc2 boost_thread-mt)
