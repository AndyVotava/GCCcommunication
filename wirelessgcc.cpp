#include "gcclibrary.hpp"

int main() {
    stdio_init_all();

    uint sm = pio_claim_unused_sm(pio0, true);

    GCconsole console1(1);
    GCcontroller controller1(0);
    GCreport origin = controller1.getorigin();
    GCreport report = controller1.getreport();
    
    while(true){

        if(console1.write(origin, report)){     //update report when console.write returns true
            report = controller1.getreport();
        }
    }

    return 0;

}