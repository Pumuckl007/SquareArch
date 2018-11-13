cmake_minimum_required(VERSION 3.2)
project(SquareArch)

set(SOURCE_FILES main.c)

add_executable(SquareArch ${SOURCE_FILES})

install(TARGETS SquareArch DESTINATION ${SQUARE_ARCH_INSTALL_BIN_DIR})
