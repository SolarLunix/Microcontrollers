/*
 * tivac_launchpad.h
 *
 *  Created on: 11 Feb 2024
 *      Author: Melissa
 */

#ifndef TIVAC_LAUNCHPAD_H_
#define TIVAC_LAUNCHPAD_H_

// Headers and naming definitions

/* Pointers to the necessary PORTF data register addresses */
//PORTD Data Register
#define GPIO_PORTD_DATA (*((volatile unsigned int*)0x400073FC))

//PORTD Direction register
#define GPIO_PORTD_DIR (*((volatile unsigned int*)0x40007400))

//PORTD Digitale Eable Register
#define GPIO_PORTD_DEN (*((volatile unsigned int*)0x4000751C))



/* Pointers to System Control register addresses*/
//System Control Register which controls the clock to PORTF
#define SYSTCTL_RCGCGPIO (*((volatile unsigned int*)0x400FE608))

//System Control Register which controls the system clock source and frequency
#define SYSTCTL_RCC (*((volatile unsigned int*)0x400FE060))

//System Control Register which shows System Control Interrupts
#define SYSTCTL_RIS (*((volatile unsigned int*)0x400FE050))

#endif /* TIVAC_LAUNCHPAD_H_ */
