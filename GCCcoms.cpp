#include "gcclibrary.h"


    uint sm = pio_claim_unused_sm(pio0, true);

    uint offset = pio_add_program(pio0, &coms_program);

    pio_sm_config c = coms_program_get_default_config(offset);



void pio_output_mode(){

    pio_sm_set_enabled(pio0, 0, false);
    pio_sm_init(pio0, 0, offset+coms_offset_outmode, &c);
    pio_sm_set_clkdiv(pio0, sm, 31.25);
    pio_sm_set_enabled(pio0, 0, true);

}

void pio_input_mode(){

    pio_sm_set_enabled(pio0, 0, false);
    pio_sm_init(pio0, 0, offset, &c);
    pio_sm_set_clkdiv(pio0, sm, 31.25);
    pio_sm_set_enabled(pio0, 0, true);

}

void pio_init(){

    sm_config_set_set_pins(&c, 0, 1);
    sm_config_set_in_pins(&c, 0);
    sm_config_set_out_pins(&c, 0, 1);
    sm_config_set_in_shift(&c, false, false, 32);
    sm_config_set_out_shift(&c, true, false, 32);

    pio_gpio_init(pio0, 0);
    pio_sm_init(pio0, sm, offset, &c);
    pio_sm_set_clkdiv(pio0, sm, 31.25);
    pio_sm_set_enabled(pio0, sm, true);
}

int main() {

    pio_init();
    pio_output_mode();
    
    while(true){
        
        pio_sm_put_blocking(pio0, sm, reversebits(0x00));
        pio_input_mode();


        sleep_ms(1000);
        
    }

}