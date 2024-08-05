#ifndef GCREPORT
#define GCREPORT

#include "pico/stdlib.h"

uint32_t to_pio(uint16_t num);


struct __attribute__((packed)) GCreport {
    uint8_t SYXBA;
    uint8_t LRZD;
    uint8_t xStick;
    uint8_t yStick;
    uint8_t cxStick;
    uint8_t cyStick;
    uint8_t analogL;
    uint8_t analogR;
};

const GCreport default_GCreport = {
    .SYXBA = 0,
    .LRZD = 128,
    .xStick = 128,
    .yStick = 128,
    .cxStick = 128,
    .cyStick = 128,
    .analogL = 0,
    .analogR = 0
};


#endif