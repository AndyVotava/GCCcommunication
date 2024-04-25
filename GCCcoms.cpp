#include "gcclibrary.hpp"
#include "hardware/watchdog.h"


int main() {
    stdio_init_all();

    uint sm = pio_claim_unused_sm(pio0, true);

    watchdog_enable(100, 1);

    GCcontroller controller1(0);
    GCconsole console1(1);

    GCreport origin = controller1.getorigin();
    GCreport report = controller1.getreport();

    
    
    while(true){

        if (console1.write(origin, report)){
            report = controller1.getreport();
        }
        watchdog_update();
        
    }
    return 0;

}