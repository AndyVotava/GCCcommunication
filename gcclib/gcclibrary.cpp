#include "gcclibrary.h"

uint8_t reversebits(uint8_t n){
    uint8_t rev = 0;
 
    for (int i = 0; i<8; i++) {
        rev <<= 1;
        if (n & 1 == 1)
            rev ^= 1;
        n >>= 1;
    }
    return rev;
}

GCcontroller::GCcontroller(uint pin):pin(pin){

    sm = pio_claim_unused_sm(pio, true);

    uint offset = pio_add_program(pio, &readgcc_program);

    pio_sm_config c = readgcc_program_get_default_config(offset);

    sm_config_set_set_pins(&c, pin, 1);
    sm_config_set_in_pins(&c, pin);
    sm_config_set_out_pins(&c, pin, 1);
    sm_config_set_in_shift(&c, false, false, 32);
    sm_config_set_out_shift(&c, true, false, 32);

    pio_gpio_init(pio, pin);
    pio_sm_init(pio, sm, offset, &c);
    pio_sm_set_clkdiv(pio, sm, 31.25);
    pio_sm_set_enabled(pio, sm, true);
}

GCreport GCcontroller::getreport(){

    pio_sm_put_blocking(pio, sm, 0x02);                 //write three byte
    pio_sm_put_blocking(pio, sm, reversebits(0x40));
    pio_sm_put_blocking(pio, sm, reversebits(0x03));
    pio_sm_put_blocking(pio, sm, reversebits(0x00));

    
    pio_sm_put_blocking(pio, sm, 0x07);                 //read eight bytes
    report.SYXBA = pio_sm_get_blocking(pio, sm);
    report.LRZD = pio_sm_get_blocking(pio, sm);
    report.xStick = pio_sm_get_blocking(pio, sm);
    report.yStick = pio_sm_get_blocking(pio, sm);
    report.cxStick = pio_sm_get_blocking(pio, sm);
    report.cyStick = pio_sm_get_blocking(pio, sm);
    report.analogL = pio_sm_get_blocking(pio, sm);
    report.analogR = pio_sm_get_blocking(pio, sm);

    
    return(report);

}

GCreport GCcontroller::getorigin(){
    
    pio_sm_put_blocking(pio, sm, 0x00);                 //write one byte
    pio_sm_put_blocking(pio, sm, reversebits(0x41));

    pio_sm_put_blocking(pio, sm, 0x09);                 //read ten bytes
    origin.SYXBA = pio_sm_get_blocking(pio, sm);
    origin.LRZD = pio_sm_get_blocking(pio, sm);
    origin.xStick = pio_sm_get_blocking(pio, sm);
    origin.yStick = pio_sm_get_blocking(pio, sm);
    origin.cxStick = pio_sm_get_blocking(pio, sm);
    origin.cyStick = pio_sm_get_blocking(pio, sm);
    origin.analogL = pio_sm_get_blocking(pio, sm);
    origin.analogR = pio_sm_get_blocking(pio, sm);
    pio_sm_get_blocking(pio, sm);
    pio_sm_get_blocking(pio, sm);

    return(origin);
}

void GCcontroller::printreport(){
    
    printf("SYXBA: %hhu LRZD: %hhu X: %hhu Y: %hhu CX: %hhu CY: %hhu L: %hhu R: %hhu\n", report.SYXBA, report.LRZD, report.xStick, report.yStick, report.cxStick, report.cyStick, report.analogL, report.analogR);

}


GCconsole::GCconsole(uint pin):pin(pin){

    sm = pio_claim_unused_sm(pio, true);        //get unused state machine in pio

    uint offset = pio_add_program(pio, &writegcc_program);  //

    pio_sm_config c = writegcc_program_get_default_config(offset);

    sm_config_set_set_pins(&c, pin, 1);
    sm_config_set_in_pins(&c, pin);
    sm_config_set_out_pins(&c, pin, 1);
    sm_config_set_in_shift(&c, false, false, 32);
    sm_config_set_out_shift(&c, true, false, 32);

    pio_gpio_init(pio, pin);
    pio_sm_init(pio, sm, offset, &c);
    pio_sm_set_clkdiv(pio, sm, 31.25);
    pio_sm_set_enabled(pio, sm, true);
}


bool GCconsole::write(GCreport origin, GCreport report){
    uint8_t request;

    request = pio_sm_get_blocking(pio, sm);

    if (request == 0x00){
        pio_sm_put_blocking(pio, sm, 0x02);        // three bytes
        pio_sm_put_blocking(pio, sm, reversebits(0x09));        //first byte to output  
        pio_sm_put_blocking(pio, sm, 0x00);                     //second byte to output
        pio_sm_put_blocking(pio, sm, reversebits(0x03));        //thrid byte to output
        return false;

    }
    
    else if(request == 0x41){                       //origin request
        pio_sm_put_blocking(pio, sm, 0x09);         //write ten bytes to console

        pio_sm_put_blocking(pio, sm, reversebits(origin.SYXBA));
        pio_sm_put_blocking(pio, sm, reversebits(origin.LRZD));
        pio_sm_put_blocking(pio, sm, reversebits(origin.xStick));
        pio_sm_put_blocking(pio, sm, reversebits(origin.yStick));
        pio_sm_put_blocking(pio, sm, reversebits(origin.cxStick));
        pio_sm_put_blocking(pio, sm, reversebits(origin.cyStick));
        pio_sm_put_blocking(pio, sm, reversebits(origin.analogL));
        pio_sm_put_blocking(pio, sm, reversebits(origin.analogR));
        pio_sm_put_blocking(pio, sm, 0x00);
        pio_sm_put_blocking(pio, sm, 0x00);
        return true;

    }

    else if(request == 0x40){
        busy_wait_us(80);
        pio_sm_put_blocking(pio, sm, 0x07);        //write eight bytes to console

        pio_sm_put_blocking(pio, sm, reversebits(report.SYXBA));
        pio_sm_put_blocking(pio, sm, reversebits(report.LRZD));
        pio_sm_put_blocking(pio, sm, reversebits(report.xStick));
        pio_sm_put_blocking(pio, sm, reversebits(report.yStick));
        pio_sm_put_blocking(pio, sm, reversebits(report.cxStick));
        pio_sm_put_blocking(pio, sm, reversebits(report.cyStick));
        pio_sm_put_blocking(pio, sm, reversebits(report.analogL));
        pio_sm_put_blocking(pio, sm, reversebits(report.analogR));
        return true;

    }
    
    else{
        printf("failed communication\n");
        printf("request = %u\n", request);
        return false;
    }
}