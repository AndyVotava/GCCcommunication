#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "joybus.pio.h"
#include "GCreport.h"
#include <stdio.h>      //for print

#define PROBE_CONTROLLER 0b111010101010101010

#define PROBE_ORIGIN 0b111110101010101110


class GCcontroller
{
private:

    uint offset;
    pio_sm_config c;    

public:
    PIO pio = pio0;
    uint sm;    
    GCreport report;
    GCreport origin;
    GCcontroller(uint8_t pin);
    uint8_t init();
    void outmode();
    void inmode();
    void get_origin();
    bool get_report();
    uint32_t pio_sm_get_with_timeout(uint32_t timeout_ms);
    bool update_report_field(uint8_t& field);

};



