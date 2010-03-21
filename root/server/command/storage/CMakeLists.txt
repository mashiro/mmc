file(GLOB MMC_SOURCES *.cpp)
add_library(mmc_storage_command STATIC ${MMC_SOURCES})
