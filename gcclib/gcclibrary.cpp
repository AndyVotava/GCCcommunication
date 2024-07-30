#include "gcclibrary.h"

GCcontroller::GCcontroller(uint8_t pin)
{
    sm = pio_claim_unused_sm(pio, true);

    offset = pio_add_program(pio, &joybus_program);

    c = joybus_program_get_default_config(offset);

    sm_config_set_set_pins(&c, pin, 1);
    sm_config_set_in_pins(&c, pin);
    sm_config_set_out_pins(&c, pin, 1);
    sm_config_set_in_shift(&c, false, true, 8);
    sm_config_set_out_shift(&c, true, false, 32);

    pio_gpio_init(pio, pin);
    pio_sm_init(pio, sm, offset, &c);
    pio_sm_set_clkdiv(pio, sm, 5);
    pio_sm_set_enabled(pio, sm, true);
}



void GCcontroller::outmode(){
    pio_sm_set_enabled(pio, sm, false);
    pio_sm_init(pio, sm, offset+joybus_offset_outmode, &c);
    pio_sm_set_clkdiv(pio, sm, 5);
    pio_sm_set_enabled(pio, sm, true);
}

void GCcontroller::inmode(){
    pio_sm_set_enabled(pio, sm, false);
    pio_sm_init(pio, sm, offset, &c);
    pio_sm_set_clkdiv(pio, sm, 5);
    pio_sm_set_enabled(pio, sm, true);
}


void GCcontroller::begin(){
        outmode();

        pio_sm_put_blocking(pio, sm, 0b111010101010101010);

        uint32_t data = pio_sm_get_blocking(pio, sm);
        printf("%d\n", data);    
        uint32_t data1 = pio_sm_get_blocking(pio, sm);
        printf("%d\n", data1);  
        uint32_t data2 = pio_sm_get_blocking(pio, sm);
        printf("%d\n", data2);  

        sleep_ms(1000);
}