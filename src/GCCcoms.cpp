#include "../include/gcclibrary.h"
#include "hardware/watchdog.h"


int main() {
    stdio_init_all();

    watchdog_enable(100, 1);

    GCcontroller controller1(0);
    GCconsole console1(1);

    controller1.getorigin();
    controller1.getreport();  //get initial values for report, TODO: make default in constructor of controller/console
    
    while(true){

        if (console1.write(controller1.origin, controller1.report)){    //input class variable report and origin
            controller1.getreport();   //Update class variable report
        }
        watchdog_update();
        
        
    }
    return 0;

}