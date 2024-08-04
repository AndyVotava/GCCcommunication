#include "gcconsole.h"

void gcconsole::outmode(){
    pio_sm_set_enabled(pio, sm, false);
    pio_sm_init(pio, sm, offset+joybus_offset_outmode, &c);
    pio_sm_set_clkdiv(pio, sm, 5);
    pio_sm_set_enabled(pio, sm, true);
}


gcconsole::gcconsole(uint8_t pin){
    sm = pio_claim_unused_sm(pio, true);

    offset = pio_add_program(pio, &joybus_program);

    c = joybus_program_get_default_config(offset);

    sm_config_set_set_pins(&c, pin, 1);
    sm_config_set_in_pins(&c, pin);
    sm_config_set_out_pins(&c, pin, 1);
    sm_config_set_in_shift(&c, false, true, 9);
    sm_config_set_out_shift(&c, true, false, 32);

    pio_gpio_init(pio, pin);
    pio_sm_init(pio, sm, offset, &c);
    pio_sm_set_clkdiv(pio, sm, 5);
    pio_sm_set_enabled(pio, sm, true);
}


void gcconsole::write_data(){
    uint8_t request = pio_sm_get_blocking(pio, sm) >> 1;


    if(request == 0x00){
        outmode();

        pio_sm_put_blocking(pio, sm, 0b10101010101010101110101110101010);
        pio_sm_put_blocking(pio, sm, 0b111110101010101011);
    }
    else if(request == 0x41)
    {

    }
    
}



