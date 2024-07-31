#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "joybus.pio.h"
#include "gc_report.h"
#include <stdio.h>      //for print

#define PROBE_CONTROLLER 0b111010101010101010

#define PROBE_ORIGIN 0b111110101010101110


class GCcontroller
{
private:
    PIO pio = pio0;
    uint sm;
    uint offset;
    pio_sm_config c;    
    gc_report report;
    gc_report origin;

public:
    GCcontroller(uint8_t pin);
    uint8_t init();
    void outmode();
    void inmode();
    void get_origin();
    void get_report();

};



