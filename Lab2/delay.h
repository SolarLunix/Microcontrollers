/*
 * delay.h
 *
 *  Created on: 11 Feb 2024
 *      Author: Solar
 */

#ifndef DELAY_H_
#define DELAY_H_

// declares a function called delayMS which returns nothing and accepts an int as input
void delayMS (int n);
// this function will create a millisecond delay and will be defined at the end of the program



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


#endif /* DELAY_H_ */
