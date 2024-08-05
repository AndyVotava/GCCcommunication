#include "GCreport.h"


uint32_t to_pio(uint16_t num) {
    uint32_t result = 0;
    uint8_t bitMask = 1;


    for(int i = 0; i < 16; i++) {
        if (num & bitMask) {
            result = (result << 2) | 0b11;
        } else {
            result = (result << 2) | 0b10;
        }
        
        num >>= 1;
    }
    
    return result;
}