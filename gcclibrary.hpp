#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "readgcc.pio.h"
#include "writegcc.pio.h"
#include <stdio.h>      //for print

uint8_t reversebits(uint8_t n){
    uint8_t rev = 0;
 
    for (int i = 0; i<8; i++) {
        rev <<= 1;
        if (n & 1 == 1)
            rev ^= 1;
        n >>= 1;
    }
    return rev;
}

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

GCcontroller::GCcontroller(uint pin):pin(pin){

    sm = pio_claim_unused_sm(pio, true);

    uint offset = pio_add_program(pio, &readgcc_program);

    pio_sm_config c = readgcc_program_get_default_config(offset);

    sm_config_set_set_pins(&c, pin, 1);
    sm_config_set_in_pins(&c, pin);
    sm_config_set_in_shift(&c, false, false, 32);
    sm_config_set_out_shift(&c, true, false, 32);

    pio_gpio_init(pio, pin);
    pio_sm_init(pio, sm, offset, &c);
    pio_sm_set_clkdiv(pio, sm, 31.25);
    pio_sm_set_enabled(pio, sm, true);
}

GCreport GCcontroller::getreport(){
    uint32_t requestreport = 0b10100000011000000000000100;   //Bits go from right to left. first bit is length indicator 0 = 24 bits, 1 = 8 bits, LAST BIT IS FOR RECIEVE LENGTH

    pio_sm_put_blocking(pio, sm, requestreport);

    report.SYXBA = pio_sm_get_blocking(pio, sm);
    report.LRZD = pio_sm_get_blocking(pio, sm);
    report.xStick = pio_sm_get_blocking(pio, sm);
    report.yStick = pio_sm_get_blocking(pio, sm);
    report.cxStick = pio_sm_get_blocking(pio, sm);
    report.cyStick = pio_sm_get_blocking(pio, sm);
    report.analogL = pio_sm_get_blocking(pio, sm);
    report.analogR = pio_sm_get_blocking(pio, sm);

    return(report);
}

GCreport GCcontroller::getorigin(){
    
    uint16_t requestorigin = 0b0100000101;  //Bits go from right to left. first bit is length indicator 0 = 24 bits, 1 = 8 bits LAST BIT IS FOR RECIEVE LENGTH

    pio_sm_put_blocking(pio, sm, requestorigin);

    origin.SYXBA = pio_sm_get_blocking(pio, sm);
    origin.LRZD = pio_sm_get_blocking(pio, sm);
    origin.xStick = pio_sm_get_blocking(pio, sm);
    origin.yStick = pio_sm_get_blocking(pio, sm);
    origin.cxStick = pio_sm_get_blocking(pio, sm);
    origin.cyStick = pio_sm_get_blocking(pio, sm);
    origin.analogL = pio_sm_get_blocking(pio, sm);
    origin.analogR = pio_sm_get_blocking(pio, sm);

    return(origin);
}

void GCcontroller::printreport(){
    
    printf("SYXBA: %hhu LRZD: %hhu X: %hhu Y: %hhu CX: %hhu CY: %hhu L: %hhu R: %hhu\n", report.SYXBA, report.LRZD, report.xStick, report.yStick, report.cxStick, report.cyStick, report.analogL, report.analogR);

}

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

GCconsole::GCconsole(uint pin):pin(pin){

    sm = pio_claim_unused_sm(pio, true);        //get unused state machine in pio

    uint offset = pio_add_program(pio, &writegcc_program);  //

    pio_sm_config c = writegcc_program_get_default_config(offset);

    sm_config_set_set_pins(&c, pin, 1);
    sm_config_set_in_pins(&c, pin);
    sm_config_set_out_pins(&c, pin, 1);
    sm_config_set_in_shift(&c, false, false, 32);
    sm_config_set_out_shift(&c, true, false, 32);

    pio_gpio_init(pio, pin);
    pio_sm_init(pio, sm, offset, &c);
    pio_sm_set_clkdiv(pio, sm, 31.25);
    pio_sm_set_enabled(pio, sm, true);
}


bool GCconsole::write(GCreport origin, GCreport report){
    uint8_t request;

    request = pio_sm_get_blocking(pio, sm);

    if (request == 0x00){
        pio_sm_put_blocking(pio, sm, 0x02);        // three bytes
        pio_sm_put_blocking(pio, sm, reversebits(0x09));        //first byte to output  
        pio_sm_put_blocking(pio, sm, 0x00);                     //second byte to output
        pio_sm_put_blocking(pio, sm, reversebits(0x03));        //thrid byte to output
        return false;

    }
    
    else if(request == 0x41){                       //origin request
        pio_sm_put_blocking(pio, sm, 0x09);         //write ten bytes to console

        pio_sm_put_blocking(pio, sm, reversebits(origin.SYXBA));
        pio_sm_put_blocking(pio, sm, reversebits(origin.LRZD));
        pio_sm_put_blocking(pio, sm, reversebits(origin.xStick));
        pio_sm_put_blocking(pio, sm, reversebits(origin.yStick));
        pio_sm_put_blocking(pio, sm, reversebits(origin.cxStick));
        pio_sm_put_blocking(pio, sm, reversebits(origin.cyStick));
        pio_sm_put_blocking(pio, sm, reversebits(origin.analogL));
        pio_sm_put_blocking(pio, sm, reversebits(origin.analogR));
        pio_sm_put_blocking(pio, sm, 0x00);
        pio_sm_put_blocking(pio, sm, 0x00);
        return true;

    }

    else if(request == 0x40){
        busy_wait_us(80);
        pio_sm_put_blocking(pio, sm, 0x07);        //write eight bytes to console

        pio_sm_put_blocking(pio, sm, reversebits(report.SYXBA));
        pio_sm_put_blocking(pio, sm, reversebits(report.LRZD));
        pio_sm_put_blocking(pio, sm, reversebits(report.xStick));
        pio_sm_put_blocking(pio, sm, reversebits(report.yStick));
        pio_sm_put_blocking(pio, sm, reversebits(report.cxStick));
        pio_sm_put_blocking(pio, sm, reversebits(report.cyStick));
        pio_sm_put_blocking(pio, sm, reversebits(report.analogL));
        pio_sm_put_blocking(pio, sm, reversebits(report.analogR));
        return true;

    }
    
    else{
        printf("failed communication\n");
        printf("request = %u\n", request);
        return false;
    }
    
    
}