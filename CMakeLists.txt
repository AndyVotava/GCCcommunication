cmake_minimum_required(VERSION 3.25)

include(pico_sdk_import.cmake)

project(wirelessgcc_project)

pico_sdk_init()

add_executable(wirelessgcc_project wirelessgcc.cpp)

pico_generate_pio_header(wirelessgcc_project ${CMAKE_CURRENT_LIST_DIR}/readgcc.pio)
pico_generate_pio_header(wirelessgcc_project ${CMAKE_CURRENT_LIST_DIR}/writegcc.pio)

target_sources(wirelessgcc_project PRIVATE wirelessgcc.cpp)

target_link_libraries(wirelessgcc_project PRIVATE pico_stdlib hardware_pio)

pico_enable_stdio_usb(wirelessgcc_project 1)     #this command is for printing for debugging

pico_add_extra_outputs(wirelessgcc_project)