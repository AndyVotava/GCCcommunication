cmake_minimum_required(VERSION 3.25)

include(pico_sdk_import.cmake)

project(GCCcoms_project)

pico_sdk_init()

add_subdirectory(gcclib)

add_executable(GCCcoms GCCcoms.cpp)

target_sources(GCCcoms PRIVATE GCCcoms.cpp)

target_link_libraries(GCCcoms PRIVATE pico_stdlib hardware_pio gcclib)

target_include_directories(GCCcoms PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/gcclib"
                          )

pico_enable_stdio_usb(GCCcoms 1)     #this command is for printing for debugging

pico_add_extra_outputs(GCCcoms)