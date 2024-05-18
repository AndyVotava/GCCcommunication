cmake_minimum_required(VERSION 3.25)

include(pico_sdk_import.cmake)

project(GCCcoms_project)

pico_sdk_init()

add_executable(GCCcoms_project src/GCCcoms.cpp src/gcclibrary.cpp)

pico_generate_pio_header(GCCcoms_project ${CMAKE_CURRENT_LIST_DIR}/pio/readgcc.pio)
pico_generate_pio_header(GCCcoms_project ${CMAKE_CURRENT_LIST_DIR}/pio/writegcc.pio)

target_sources(GCCcoms_project PRIVATE src/GCCcoms.cpp)

target_link_libraries(GCCcoms_project PRIVATE pico_stdlib hardware_pio)

pico_enable_stdio_usb(GCCcoms_project 1)     #this command is for printing for debugging

pico_add_extra_outputs(GCCcoms_project)