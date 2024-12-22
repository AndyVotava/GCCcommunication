#include "gccontroller.h"
#include "gcconsole.h"


GCcontroller controller(0);
gcconsole gamecubeconsole(1);

void callback(uint gpio, uint32_t events){
    gpio_set_irq_enabled_with_callback(1, GPIO_IRQ_EDGE_FALL, false, &callback);

    if(!gamecubeconsole.write_data(controller.origin, controller.report)){
        gpio_put(PICO_DEFAULT_LED_PIN, true);   //An error occured
    }

    gpio_set_irq_enabled_with_callback(1, GPIO_IRQ_EDGE_FALL, true, &callback);

}

int main() {

    gpio_init(PICO_DEFAULT_LED_PIN);

    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
    //stdio_init_all();


    controller.origin = default_GCreport;
    controller.report = default_GCreport;

    controller.init();
    busy_wait_us(25);
    controller.get_origin();
    busy_wait_us(100);
    controller.get_report();
    busy_wait_us(100);

    gpio_set_irq_enabled_with_callback(1, GPIO_IRQ_EDGE_FALL, true, &callback);
    
    while(true){
        controller.get_report();
        busy_wait_us(100);

    }

}