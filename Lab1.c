
#include "inc/tm4c1294ncpdt.h"
#include <stdint.h>

void main(void)
{
    int i = 0;

    // Enable the clock for GPIO ports N , J and F
    SYSCTL_RCGCGPIO_R = 0x00001120;

    i++;

    // Configure port N for digital output
    GPIO_PORTN_DEN_R = 0x03;
    GPIO_PORTN_DIR_R = 0x03;

    // Configure port F for digital output
    GPIO_PORTF_AHB_DEN_R = 0x11;
    GPIO_PORTF_AHB_DIR_R = 0x11;

    // Enable weak pull-up for PIN PJ0 and PJ1 (SW1 and SW2)
    GPIO_PORTJ_AHB_DEN_R = 0x03;
    GPIO_PORTJ_AHB_DIR_R = 0x00;
    GPIO_PORTJ_AHB_PUR_R = 0x03;


    // Main loop
    while (1)
    {
        if (GPIO_PORTJ_AHB_DATA_R == 0x02)  // Check SW1  J0
        {
            // Two LEDs alternate on the left
            GPIO_PORTN_DATA_R = 0x02;// PN1 LED D1 will turn ONN
            for (i = 0; i < 500000; i++);
            GPIO_PORTN_DATA_R = 0x01;//PN0 LED D2
            for (i = 0; i < 500000; i++);
            GPIO_PORTN_DATA_R = 0x00;
        }
        else if (GPIO_PORTJ_AHB_DATA_R == 0x01)  // Check SW2
        {
            GPIO_PORTF_AHB_DATA_R = 0x10; // =>PIN4(D3)
            for (i = 0; i < 500000; i++); //
            GPIO_PORTF_AHB_DATA_R = 0x01; // =>PN0(D4)
            for (i = 0; i < 500000; i++); //
            GPIO_PORTF_AHB_DATA_R = 0x00;
        }
        else if (GPIO_PORTJ_AHB_DATA_R == 0x00) // alternating the pairs Of Switches,
        {
            GPIO_PORTN_DATA_R = 0x02;// D1
            GPIO_PORTF_AHB_DATA_R = 0x10; // =>D3
            for (i = 0; i < 500000; i++); // =>
            GPIO_PORTN_DATA_R = 0x01; // => D2
            GPIO_PORTF_AHB_DATA_R = 0x01;//D4
            for (i = 0; i < 500000; i++); // =>
            GPIO_PORTN_DATA_R = 0x00;
            GPIO_PORTF_AHB_DATA_R = 0x00;


        }
    }
}

