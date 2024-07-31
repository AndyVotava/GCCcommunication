#include "gccontroller.h"

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


uint8_t GCcontroller::init(){
    outmode();

    pio_sm_put_blocking(pio, sm, PROBE_CONTROLLER);

    uint8_t resp0 = pio_sm_get_blocking(pio, sm);
    uint8_t resp1 = pio_sm_get_blocking(pio, sm);
    uint8_t resp2 = pio_sm_get_blocking(pio, sm);

    return resp0, resp1, resp2;
}

void GCcontroller::get_origin(){
    outmode();

    pio_sm_put_blocking(pio, sm, PROBE_ORIGIN);

    origin.SYXBA = pio_sm_get_blocking(pio, sm);
    origin.LRZD = pio_sm_get_blocking(pio, sm);
    origin.xStick = pio_sm_get_blocking(pio, sm);
    origin.yStick = pio_sm_get_blocking(pio, sm);
    origin.cxStick = pio_sm_get_blocking(pio, sm);
    origin.cyStick = pio_sm_get_blocking(pio, sm);
    origin.analogL = pio_sm_get_blocking(pio, sm);
    origin.analogL = pio_sm_get_blocking(pio, sm);
}

void GCcontroller::get_report(){
    outmode();

    pio_sm_put_blocking(pio, sm, 0b11111010101010101010101010101110);
    pio_sm_put_blocking(pio, sm, 0b111010101010101010);
    
    report.SYXBA = pio_sm_get_blocking(pio, sm);
    report.LRZD = pio_sm_get_blocking(pio, sm);
    report.xStick = pio_sm_get_blocking(pio, sm);
    report.yStick = pio_sm_get_blocking(pio, sm);
    report.cxStick = pio_sm_get_blocking(pio, sm);
    report.cyStick = pio_sm_get_blocking(pio, sm);
    report.analogL = pio_sm_get_blocking(pio, sm);
    report.analogL = pio_sm_get_blocking(pio, sm);

}