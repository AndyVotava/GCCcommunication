#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "readgcc.pio.h"
#include "writegcc.pio.h"
#include <stdio.h>      //for print

uint8_t reversebits(uint8_t n);


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

class GCcontroller{
    public:
    uint pin;
    GCcontroller(uint pin);
    GCreport getreport();
    void printreport();
    GCreport getorigin();
    void printorigin();

    private:
    PIO pio = pio1;
    uint sm; 
    GCreport origin;
    GCreport report;
};

class GCconsole
{
public:
uint pin;
GCconsole(uint pin);
bool write(GCreport origin, GCreport report);

private:
PIO pio = pio0;
uint sm;
};