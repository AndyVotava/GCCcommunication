#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "readgcc.pio.h"
#include "writegcc.pio.h"
#include <stdio.h>      //for print

//uint16_t status = 0b000000001;          //first bit to set length to 9 -> 8 bits of probe + end bit
//uint16_t origin = 0b100000101;


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
    PIO pio;
    uint sm; 
    uint pin;
    GCcontroller(PIO pio, uint pin);

    void getreport();
    void printreport();
    void getorigin();
    void printorigin();

    protected:
    GCreport origin;
    GCreport report;


};

GCcontroller::GCcontroller(PIO pio, uint pin): pio(pio), pin(pin){

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

void GCcontroller::getreport(){
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

}

void GCcontroller::getorigin(){
    
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
}

void GCcontroller::printreport(){
    
    printf("SYXBA: %hhu LRZD: %hhu X: %hhu Y: %hhu CX: %hhu CY: %hhu L: %hhu R: %hhu\n", report.SYXBA, report.LRZD, report.xStick, report.yStick, report.cxStick, report.cyStick, report.analogL, report.analogR);

}

class GCconsole
{
public:
PIO pio;
uint sm;
uint pin;
GCconsole(PIO pio, uint pin);
void write(GCreport data);

};

GCconsole::GCconsole(PIO pio, uint pin): pio(pio), pin(pin){

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

void GCconsole::write(GCreport data){
    uint32_t gccresponse = 0b110000000000000010010000; 
    uint8_t one = 0b0;
    uint8_t three = 0b10;
    uint8_t eight = 0b111;
    uint8_t ten = 0b1001;
    uint16_t consolerequest;

    pio_sm_put_blocking(pio, sm, one);
    consolerequest = pio_sm_get_blocking(pio, sm);
    printf("%u\n", consolerequest);

    if (consolerequest != 0){
        //reset pio
        busy_wait_us(1);
    }
        pio_sm_put_blocking(pio, sm, three);
        pio_sm_put_blocking(pio, sm, gccresponse);    

    busy_wait_ms(1);

}
