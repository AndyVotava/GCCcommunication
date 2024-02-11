// -------------------------------------------------- //
// This file is autogenerated by pioasm; do not edit! //
// -------------------------------------------------- //

#pragma once

#if !PICO_NO_HARDWARE
#include "hardware/pio.h"
#endif

// ---------- //
// squarewave //
// ---------- //

#define squarewave_wrap_target 0
#define squarewave_wrap 20

static const uint16_t squarewave_program_instructions[] = {
            //     .wrap_target
    0xe081, //  0: set    pindirs, 1                 
    0x80a0, //  1: pull   block                      
    0x6021, //  2: out    x, 1                       
    0x0026, //  3: jmp    !x, 6                      
    0xe048, //  4: set    y, 8                       
    0x0008, //  5: jmp    8                          
    0xe058, //  6: set    y, 24                      
    0x0008, //  7: jmp    8                          
    0x6021, //  8: out    x, 1                       
    0x002e, //  9: jmp    !x, 14                     
    0xe400, // 10: set    pins, 0                [4] 
    0xeb01, // 11: set    pins, 1                [11]
    0x0088, // 12: jmp    y--, 8                     
    0x0012, // 13: jmp    18                         
    0xee00, // 14: set    pins, 0                [14]
    0xe101, // 15: set    pins, 1                [1] 
    0x0088, // 16: jmp    y--, 8                     
    0x0012, // 17: jmp    18                         
    0xe080, // 18: set    pindirs, 0                 
    0xbf42, // 19: nop                           [31]
    0xbf42, // 20: nop                           [31]
            //     .wrap
};

#if !PICO_NO_HARDWARE
static const struct pio_program squarewave_program = {
    .instructions = squarewave_program_instructions,
    .length = 21,
    .origin = -1,
};

static inline pio_sm_config squarewave_program_get_default_config(uint offset) {
    pio_sm_config c = pio_get_default_sm_config();
    sm_config_set_wrap(&c, offset + squarewave_wrap_target, offset + squarewave_wrap);
    return c;
}
#endif

