#include "gcclibrary.hpp"

int main() {
    stdio_init_all();

    uint sm = pio_claim_unused_sm(pio0, true);

    GCcontroller controller1(0);
    GCconsole console1(1);

    GCreport origin = controller1.getorigin();
    busy_wait_ms(3);
    GCreport report = controller1.getreport();
    
    while(true){

        if(console1.write(origin, report)){
        report = controller1.getreport(); 
        }
        
    }
    return 0;

}