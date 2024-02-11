/*
 * SYSCLKCONFIG.h
 *
 *  Created on: 11 Feb 2024
 *      Author: Solar
 */

#ifndef SYSCLKCONFIG_H_
#define SYSCLKCONFIG_H_

// declares a function called SYSCLKCONFIG which returns nothing and accepts nothing
void SYSCLKCONFIG (void);
// It will configure the system clock to run at 50Mhz and will be defined at the end of the program



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


#endif /* SYSCLKCONFIG_H_ */
