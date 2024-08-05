#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "joybus.pio.h"
#include "GCreport.h"
#include <stdio.h>      //for print

#define TWO_NULL_BYTES 0b10101010101010101010101010101010


class gcconsole
{
private:
    PIO pio = pio1;
    uint sm;
    uint offset;
    pio_sm_config c;    

    void outmode();
    
public:
    gcconsole(uint8_t pin);
    bool write_data();
};
