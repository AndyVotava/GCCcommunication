#include "gccontroller.h"


int main() {

    stdio_init_all();

    GCcontroller controller(0);

        controller.init();
        sleep_us(25);
        controller.get_origin();
        sleep_us(100);

    while(true){
        
        controller.get_report();
        sleep_us(100);
        
    }

}