#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "joybus.pio.h"
#include <stdio.h>      //for print

struct __attribute__((packed)) GCreport {
    public:
    uint8_t SYXBA;
    uint8_t LRZD;
    uint8_t xStick;
    uint8_t yStick;
    uint8_t cxStick;
    uint8_t cyStick;
    uint8_t analogL;
    uint8_t analogR;
};

class GCcontroller
{
private:
    /* data */
public:
    GCcontroller(uint8_t pin);
    void begin();
    void outmode();
    void inmode();

    PIO pio = pio0;
    uint sm;
    uint offset;
    pio_sm_config c;
};



