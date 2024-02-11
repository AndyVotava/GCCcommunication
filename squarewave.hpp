static inline void squarewave_init(PIO pio, uint sm, uint offset, uint pin){

    pio_sm_config c = squarewave_program_get_default_config(offset);

    sm_config_set_set_pins(&c, pin, 1);
    sm_config_set_in_shift(&c, true, false, 32);
    sm_config_set_out_shift(&c, true, false, 32);

    pio_gpio_init(pio, pin);
    pio_sm_init(pio, sm, offset, &c);
    pio_sm_set_clkdiv(pio, sm, 31.25);
    pio_sm_set_enabled(pio, sm, true);
}