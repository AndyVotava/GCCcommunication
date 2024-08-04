#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "joybus.pio.h"
#include "gc_report.h"
#include <stdio.h>      //for print

#define CONTROLLER_PROBE_RESPONSE

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
    void write_data();
};
