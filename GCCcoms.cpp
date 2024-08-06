#include "gccontroller.h"
#include "gcconsole.h"


int main() {

    stdio_init_all();

    GCcontroller controller(0);
    gcconsole gamecubeconsole(1);

    controller.init();
    sleep_us(25);
    controller.get_origin();
    sleep_us(100);
    controller.get_report();

    while(true){
        
        if(gamecubeconsole.write_data(controller.origin, controller.report)){
            controller.get_report();
        }

    }
}