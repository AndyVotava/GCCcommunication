#include "pico/stdlib.h"
#include "hardware/pio.h"

//uint16_t status = 0b000000001;          //first bit to set length to 9 -> 8 bits of probe + end bit
//uint16_t origin = 0b100000101;


struct __attribute__((packed)) GCreport {
    private:
    uint8_t a : 1; uint8_t b : 1; uint8_t x:1; uint8_t y : 1; uint8_t start : 1; uint8_t pad0 : 3;
    uint8_t dLeft : 1; uint8_t dRight : 1; uint8_t dDown : 1; uint8_t dUp : 1; uint8_t z : 1; uint8_t r : 1; uint8_t l : 1; uint8_t pad1 : 1;
    uint8_t xStick;
    uint8_t yStick;
    uint8_t cxStick;
    uint8_t cyStick;
    uint8_t analogL;
    uint8_t analogR;
};

class GCcontroller : protected GCreport {
    public:
    PIO pio;
    uint sm; 
    GCcontroller(PIO pio, uint sm, uint pin);

    void getreport();
    void getorigin();
};

GCcontroller::GCcontroller(PIO pio, uint sm, uint pin): pio(pio), sm(sm){

    uint offset = pio_add_program(pio, &squarewave_program);

    pio_sm_config c = squarewave_program_get_default_config(offset);

    sm_config_set_set_pins(&c, pin, 1);
    sm_config_set_in_shift(&c, false, true, 32);
    sm_config_set_out_shift(&c, true, false, 32);

    pio_gpio_init(pio, pin);
    pio_sm_init(pio, sm, offset, &c);
    pio_sm_set_clkdiv(pio, sm, 31.25);
    pio_sm_set_enabled(pio, sm, true);
}

void GCcontroller::getreport(){
    uint32_t requestreport = 0b0100000011000000000000100;   //Bits go from right to left. first bit is length indicator 0 = 24 bits, 1 = 8 bits
    uint8_t recievebitlength = 0b00;                        //64 bits sent from controller
    pio_sm_put_blocking(pio, sm, requestreport);
}

void GCcontroller::getorigin(){
    uint16_t requestorigin = 0b100000101;  //Bits go from right to left. first bit is length indicator 0 = 24 bits, 1 = 8 bits
    uint8_t recievebitlength = 0b00;                //80 bits sent from controller
    pio_sm_put_blocking(pio, sm, requestorigin);
    pio_sm_get_blocking(pio, sm);
}