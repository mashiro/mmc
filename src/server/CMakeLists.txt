set(NAME mmc_server)

file(GLOB MMC_SERVER_SOURCES *.cpp *.hpp)
file(GLOB MMC_COMMAND_SOURCES command/*.cpp command/*.hpp)
file(GLOB MMC_CACHE_SOURCES cache/*.cpp cache/*.hpp)

add_library(${NAME} STATIC
	${MMC_SERVER_SOURCES}
	${MMC_COMMAND_SOURCES}
	${MMC_CACHE_SOURCES}
)
