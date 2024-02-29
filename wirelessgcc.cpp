#include "gcclibrary.hpp"

int main() {
    stdio_init_all();

    uint sm = pio_claim_unused_sm(pio0, true);

    GCconsole console1(pio1, 1);
    GCcontroller controller1(pio0, 0);
    
    while(true){

        console1.write();

    }

    return 0;

}