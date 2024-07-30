#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "readgcc.pio.h"
#include "writegcc.pio.h"
#include "coms.pio.h"
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
    GCreport origin;
    GCreport report;

    GCcontroller(uint pin);

    //This function polls the Gamecube controller for report and writes it to the private variable report, then returns it.
    GCreport getreport();

    //Prints the private variable report.
    void printreport();
    
    //This function polls the Gamecube controller for origin and writes it to the private variable origin, then returns it.
    GCreport getorigin();

    //Prints the private variable origin.
    void printorigin();


    PIO pio = pio1;
    uint sm; 
    uint offset;
    pio_sm_config c;
    private:

};


class GCconsole
{
public:
uint pin;
GCconsole(uint pin);

//Writes data to console baised on console request, returns true when Gamcube controller should be polled for data.
bool write(GCreport origin, GCreport report);

private:
PIO pio = pio0;
uint sm;
};