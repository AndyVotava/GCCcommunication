#include "gccontroller.h"

uint32_t GCcontroller::pio_sm_get_with_timeout(uint32_t timeout_us) {
    uint32_t start_time = time_us_32();

    while (true) {
        if (!pio_sm_is_rx_fifo_empty(pio, sm)) {
            return pio_sm_get(pio, sm); 
        }

        if (time_us_32() - start_time > timeout_us) {
            return 0xFFFFFFFF;
        }
    }
}

bool GCcontroller::update_report_field(uint8_t& field) {
    uint32_t value = pio_sm_get_with_timeout(200);
    if (value != 0xFFFFFFFF) {
        field = value;
        return true;
    }
    return false;
}


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

bool GCcontroller::get_report(){
    outmode();
    pio_sm_put_blocking(pio, sm, 0b11111010101010101010101010101110);   //ask controller for report
    pio_sm_put_blocking(pio, sm, 0b111010101010101010);
    
    if(!update_report_field(report.SYXBA))return false;
    if(!update_report_field(report.LRZD))return false;
    if(!update_report_field(report.xStick))return false;
    if(!update_report_field(report.yStick))return false;
    if(!update_report_field(report.cxStick))return false;
    if(!update_report_field(report.cyStick))return false;
    if(!update_report_field(report.analogL))return false;
    if(!update_report_field(report.analogR))return false;

    return true;
}