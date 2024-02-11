#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "squarewave.pio.h"
#include "squarewave.hpp"

uint16_t probe = 0x00;
uint16_t origin = 0x41;


int main() {
    PIO pio = pio0;
    //FIRST BIT ON RIGHT!!
    uint16_t probe = 0b1000000001;          //first bit to set length to 9 -> 8 bits of probe + end bit
    uint16_t origin = 0b1100000101;
    uint32_t request = 0b10100000011000000000000100;
   
   uint offset = pio_add_program(pio, &squarewave_program);
   uint sm = pio_claim_unused_sm(pio, true);
   squarewave_init(pio, sm, offset, 0);


   while(true){
        pio_sm_put_blocking(pio, sm, probe);         //first bit to determine length of probe, 1 = 8 bits + 1 end bit, 0 = 24 bits + 1 end bit
        pio_sm_put_blocking(pio, sm, origin);
        pio_sm_put_blocking(pio, sm, request);

   }

    return 0;

}


