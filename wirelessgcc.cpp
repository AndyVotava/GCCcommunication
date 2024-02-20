#include "readgcc.pio.h"
#include "gcclibrary.hpp"

int main() {
    stdio_init_all();

    uint sm = pio_claim_unused_sm(pio0, true);

    GCcontroller controller1(pio0, 0);

    
    while(true){

        controller1.getreport();
        controller1.printreport();

    }

    return 0;

}