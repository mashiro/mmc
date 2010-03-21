add_subdirectory(storage)

file(GLOB MMC_SOURCES *.cpp)
add_library(mmc_command STATIC ${MMC_SOURCES})
target_link_libraries(mmc_command mmc_storage_command)
