/********************************/
// Intro to Microcontrollers    //
/********************************/

// Headers and naming definitions

/* Pointers to the necessary PORTF data register addresses */
//PORTF Data Register
#define GPIO_PORTF_DATA (*((volatile unsigned int*)0x400253FC))

//PORTF Direction register
#define GPIO_PORTF_DIR (*((volatile unsigned int*)0x40025400))

//PORTF Digitale Eable Register
#define GPIO_PORTF_DEN (*((volatile unsigned int*)0x4002551C))


/* Pointers to System Control register addresses*/
//System Control Register which controls the clock to PORTF
#define SYSTCTL_RCGCGPIO (*((volatile unsigned int*)0x400FE608))

//System Control Register which controls the system clock source and frequency
#define SYSTCTL_RCC (*((volatile unsigned int*)0x400FE060))

//System Control Register which shows System Control Interrupts
#define SYSTCTL_RIS (*((volatile unsigned int*)0x400FE050))


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
#define Purple 0b00000110
#define Teal 0b00001100
#define Yellow 0b00001010

// declares a function called delayMS which returns nothing and accepts an int as input
void delayMS (int n);
// this function will create a millisecond delay and will be defined at the end of the program

// declares a function called SYSCLKCONFIG which returns nothing and accepts nothing
void SYSCLKCONFIG (void);
// It will configure the system clock to run at 50Mhz and will be defined at the end of the program

int main(void)
{
    SYSCLKCONFIG(); // Configures System clock to run at 50MHz
    SYSTCTL_RCGCGPIO |= 0x20; // Starts the clock to PORTF
    GPIO_PORTF_DIR |= 0x0E; // Sets Pins 1, 2, and 3 of PORTF as digital outputs
    GPIO_PORTF_DEN |= 0x0E; // Sets Pins 1, 2, and 3 of PORTF as digital pins

    while(1) //infinite loop
    {
        GPIO_PORTF_DATA = Red;  // turn on the red led
        delayMS(5000);           // Delay half a second
        GPIO_PORTF_DATA = Purple;
        delayMS(5000);
        GPIO_PORTF_DATA = Blue;
        delayMS(5000);
        GPIO_PORTF_DATA = Teal;
        delayMS(5000);
        GPIO_PORTF_DATA = Green;
        delayMS(5000);
        GPIO_PORTF_DATA = Yellow;
        delayMS(5000);
        GPIO_PORTF_DATA = Red;
        delayMS(5000);
        GPIO_PORTF_DATA = White;
        delayMS(5000);
        GPIO_PORTF_DATA = 0x00; // Turn off red LED
        delayMS(5000);           // Delay half a second
    }
}


/**************************************************/
//          delayMS function                      //
// returns nothing (void)                         //
// accepts an int as input (int n)                //
// creates a delay of ~1ms in the inner for loop  //
// the loop runs n times                          //
/**************************************************/

void delayMS (int n)
{
    int i, j;
    for (i=0; i<n; i++)
    {
        for (j=0; j<400; j++)
        {

        }
    }
}


/**************************************************/
//          SYSCLKCONFIG                          //
// returns nothing (void)                         //
// accepts nothing (void)                         //
// sets up the system clock to use the onboard    //
// 16MHz crystal to drive the onboard PLL at      //
// 400MHz before dividing the PLL by 4 to produce //
// a 50Mhz system clock frequency                 //
/**************************************************/

void SYSCLKCONFIG(void)
{
    /* 1. Bypass the PLL and system clock divider by setting the BYPASS bit[11]
     *    and clearing the USESYS bit[22] in the RCC register, thereby configuring
     *    the microcontroller to run off a "raw" clock source and allowing for the
     *    new PLL configuration to be validated before switching the system clock
     *    to the PLL
     * |= sets
     * &= clears
     */
    SYSTCTL_RCC |= 0x00000800;
    SYSTCTL_RCC &= 0xFFBFFFFF;


    /* 2. Select the crystal value (XTAL) bits[10:6] and oscillator source (OSCSRC)
     *    bits[5:4], and clear the PWRDN bit[13] in RCC/RCC2 system control register.
     * 16MHz XTAL[10:16 = 0x15 and select MOSC source OSCSRC[5:4] = 0x0
     *    = 0b 1111 1111 1111 1111 1101 1101 0100 1111 = 0xFFFFFD4F
     */
    SYSTCTL_RCC |= 0x00000D40; // set bit 6, 8, and 10
    SYSTCTL_RCC &= 0xFFFFDD4F; // clears bit 13


    /* 3. Select the desired system divider (SYSDIV) in RCC/RCC2 and set the USESYS
     *    bit in RCC. The SYSDIV field determines the system frequency for the
     *    microcontroller.
     *      0x03 => divide by 4 i.e. bits 26 and 25 = 0 and 24 and 23 = 1
     */
    SYSTCTL_RCC |= 0x01C00000;
    SYSTCTL_RCC &= 0xF9FFFFFF;


    /* 4. Wait for the PLL to lock by polling the PLLLRIS in the Raw Interrupt Status
     *    (RIS) register
     */
    while((SYSTCTL_RIS & 0x00000040) == 0)
    {

    }

    /* 5.Enable the use of the PLL by clearing the BYPASS bit in RCC/RCC2.
     */
    SYSTCTL_RCC &= 0xFFFFF7FF;
}
