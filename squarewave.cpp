#include "squarewave.pio.h"
#include "squarewave.hpp"

int main() {

    uint sm = pio_claim_unused_sm(pio0, true);

    GCcontroller controller1(pio0, sm, 0);


    while(true){

        controller1.getorigin();
        controller1.getreport();

    }

    return 0;

}


