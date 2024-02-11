#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "squarewave.pio.h"
#include "squarewave.hpp"

int main() {
    GCcontroller controller1;

    controller1.pio = pio0;
    controller1.sm = pio_claim_unused_sm(controller1.pio, true);
   
    controller1.init(0);

    while(true){

        controller1.getreport();

    }

    return 0;

}


