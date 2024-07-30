add_library(gcclib gcclibrary.cpp)

target_link_libraries(gcclib 
      pico_stdlib
      hardware_pio
)

pico_generate_pio_header(gcclib ${CMAKE_CURRENT_LIST_DIR}/pio/readgcc.pio)
pico_generate_pio_header(gcclib ${CMAKE_CURRENT_LIST_DIR}/pio/writegcc.pio)
pico_generate_pio_header(gcclib ${CMAKE_CURRENT_LIST_DIR}/pio/coms.pio)
