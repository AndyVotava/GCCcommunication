#include "gcclibrary.h"

GCcontroller::GCcontroller(uint8_t pin)
{
    printf("began initialization");

    sm = pio_claim_unused_sm(pio0, true);

    offset = pio_add_program(pio0, &joybus_program);

    c = joybus_program_get_default_config(offset);

    sm_config_set_set_pins(&c, 0, 1);
    sm_config_set_in_pins(&c, 0);
    sm_config_set_out_pins(&c, 0, 1);
    sm_config_set_in_shift(&c, false, true, 8);
    sm_config_set_out_shift(&c, true, false, 32);

    pio_gpio_init(pio0, 0);
    pio_sm_init(pio0, sm, offset, &c);
    pio_sm_set_clkdiv(pio0, sm, 5);
    pio_sm_set_enabled(pio0, sm, true);

    printf("completed initialization");
}



void GCcontroller::outmode(){
    pio_sm_set_enabled(pio0, 0, false);
    pio_sm_init(pio0, 0, offset+joybus_offset_outmode, &c);
    pio_sm_set_clkdiv(pio0, sm, 5);
    pio_sm_set_enabled(pio0, 0, true);
}

void GCcontroller::inmode(){
    pio_sm_set_enabled(pio0, 0, false);
    pio_sm_init(pio0, 0, offset, &c);
    pio_sm_set_clkdiv(pio0, sm, 5);
    pio_sm_set_enabled(pio0, 0, true);
}


void GCcontroller::begin(){
        outmode();

        pio_sm_put_blocking(pio0, sm, 0b111010101010101010);

        uint32_t data = pio_sm_get_blocking(pio0, sm);
        printf("%d\n", data);    
        uint32_t data1 = pio_sm_get_blocking(pio0, sm);
        printf("%d\n", data1);  
        uint32_t data2 = pio_sm_get_blocking(pio0, sm);
        printf("%d\n", data2);  

        sleep_ms(1000);
}