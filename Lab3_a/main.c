/********************************/
// Intro to Microcontrollers    //
/********************************/

// Headers and naming definitions

#include "tivac_launchpad.h"
#include "SYSCLKCONFIG.H"
#include "delay.h"

int main(void)
{
    // Run at 50MHz
    SYSCLKCONFIG();

    // Start the Port D clock
    SYSTCTL_RCGCGPIO |= PORTD_CLK;

    // Set pin 0 PORTD as digital output and pin
    GPIO_PORTD_DIR |= 0x01;
    GPIO_PORTD_DEN |= 0x01;

    while(1)
    {
        // turn off, delay half second, turn off delay half second, repeat
        GPIO_PORTD_DATA |= 0x01;
        delayMS(500);
        GPIO_PORTD_DATA &= ~0x01;
        delayMS(500);
    }
}
