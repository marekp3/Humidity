#include <stdint.h>
#include <stdio.h>
int main()
{


    uint16_t crc = 0;
    uint16_t hum_wart = 652;
    uint16_t temp = 351;

    
    crc = (hum_wart & ~(~0<<8)) + ((hum_wart & (~(~0<<8))<<8)>>8);
    crc = crc + (temp & ~(~0<<8)) + ((temp & (~(~0<<8))<<8)>>8);
    crc = crc & ~(~0<<8);

    printf("%d", crc);

    return(0);
}