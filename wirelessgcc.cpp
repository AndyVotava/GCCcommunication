#include "gcclibrary.hpp"

int main() {
    stdio_init_all();

    uint sm = pio_claim_unused_sm(pio0, true);

    GCconsole console1(pio1, 1);
    GCcontroller controller1(pio0, 0);
    
    while(true){

        console1.write();
        //printf("controller sm: %u pio: %u pin:%u\t   console sm: %u pio: %u pin: %u\n",controller1.pio, controller1.sm, controller1.pin, console1.pio, console1.sm, console1.pin);

    }

    return 0;

}