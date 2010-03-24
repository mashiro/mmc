set(NAME mmc_command)

file(GLOB MMC_COMMAND_SOURCES *.cpp *.hpp)
add_library(${NAME} STATIC ${MMC_COMMAND_SOURCES})
