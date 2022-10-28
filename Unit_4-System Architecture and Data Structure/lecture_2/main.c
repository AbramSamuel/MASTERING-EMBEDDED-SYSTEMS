/*
 * main.c
 *
 *  Created on: Oct 20, 2022
 *      Author: ABRAM
 */


#include "DC_Motor.h"
#include "US_Sensor.h"
#include "Collision_Avoidance.h"



void setup ()
{
	//init all the drivers
	//init IRQ ...
	//init HAL US_Driver DC_Driver
	//init block
	US_INITIALIZE();
	DC_INITIALIZE();
//set states pointers for each block
	CA_state = STATE(CA_WAITING);
	US_state = STATE(US_busy);
	DC_state = STATE(DC_idle);

}

int main()
{
 setup();
while(1)
{
	volatile int d;
	//call state for each block
	US_state();
	CA_state();
	DC_state();
	//delay
	for(d=0 ; d<=1000 ; d++);
}

return 0 ;
}
