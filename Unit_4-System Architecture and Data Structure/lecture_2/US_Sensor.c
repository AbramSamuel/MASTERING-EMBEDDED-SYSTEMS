/*
 * US.c
 *
 *  Created on: Oct 21, 2022
 *      Author: ABRAM
 */

#include "US_Sensor.h"


enum
{
	US_busy
}US_state_id;

void (*US_state)();


//module variable
unsigned int distance;

int Generate_random(int min,int max, int n)
{
	int i;
	for(i=0; i <n;i++)
	{
		int rand_val = (rand()%(max-min+1))+min;
		return rand_val;
	}
}

//Initialize the US sensor
void US_INITIALIZE()
{
	printf("US SENSOR INITIALIZED\n");
}

STATE_DEFINE(US_busy)
{
	//	state action
	int distance = Generate_random(45, 55, 1);
	printf("\nUS Sensor busy state: Distance=%d\n",distance);

	US_Get_Distance(distance);
	US_state = STATE(US_busy);
}
