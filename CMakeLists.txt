cmake_minimum_required(VERSION 3.25)

include(pico_sdk_import.cmake)

project(pio_squarewave)

pico_sdk_init()

add_executable(pio_squarewave)

pico_generate_pio_header(pio_squarewave ${CMAKE_CURRENT_LIST_DIR}/squarewave.pio)

target_sources(pio_squarewave PRIVATE squarewave.cpp)

target_link_libraries(pio_squarewave PRIVATE pico_stdlib hardware_pio)

pico_enable_stdio_usb(pio_squarewave 1)     #this command is for printing for debugging

pico_add_extra_outputs(pio_squarewave)

file(MAKE_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/generated)
# generate .hex file and .pio.h file for the RP2040 datasheet (to make sure
# the datasheet always shows the output of the latest pioasm version)
