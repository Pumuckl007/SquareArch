cmake_minimum_required(VERSION 3.2)
project(SquareArchSim_tests)

include_directories(${SQUARE_ARCH_HEADERS_DIR})

set(SOURCE_FILES test_maxint.c)

add_executable(SquareArchSim_tests ${SOURCE_FILES})

link_directories(/usr/lib/)

set_target_properties (SquareArchSim_tests PROPERTIES LINK_FLAGS "-Wall")

target_link_libraries(SquareArchSim_tests -lcunit)

add_test (test_lib ${EXECUTABLE_OUTPUT_PATH}/test_sim)
