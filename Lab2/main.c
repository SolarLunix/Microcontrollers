/********************************/
// Intro to Microcontrollers    //
/********************************/

// Headers and naming definitions

#include "tivac_launchpad.h"
#include "SYSCLKCONFIG.H"
#include "delay.h"


/* Declare definitions to correct bits which control the 3 LEDs
 * red LED is Pin1 of PORTF (0010 0x02)
 * blue LED is Pin 2 of PORTF (0100 or 0x04)
 * green LED is Pin 3 of PORTF (1000 or 0x08)
 * by turning all 3 LEDs on we can get a white light (1110 or 0x0E)
 */
#define Red 0x02    //0b00000010
#define Blue 0x04   //0b00000100
#define Green 0x08  //0b00001000
#define White 0x0E  //0b00001110


int main(void)
{
    SYSCLKCONFIG(); // Configures System clock to run at 50MHz
    SYSTCTL_RCGCGPIO |= 0x20; // Starts the clock to PORTF
    GPIO_PORTF_DIR |= 0x0E; // Sets Pins 1, 2, and 3 of PORTF as digital outputs
    GPIO_PORTF_DEN |= 0x0E; // Sets Pins 1, 2, and 3 of PORTF as digital pins

    while(1) //infinite loop
    {
        GPIO_PORTF_DATA = Blue;  // turn on the red led
        delayMS(5000);           // Delay half a second
        GPIO_PORTF_DATA = 0x00; // Turn off red LED
        delayMS(5000);           // Delay half a second
    }
}
