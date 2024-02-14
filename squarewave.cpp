#include "squarewave.pio.h"
#include "squarewave.hpp"

int main() {
    stdio_init_all();

    uint sm = pio_claim_unused_sm(pio0, true);

    GCcontroller controller1(pio0, sm, 0);

    
    while(true){

        controller1.getreport();

    }

    return 0;

}