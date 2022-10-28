/*
 * DC.c
 *
 *  Created on: Oct 21, 2022
 *      Author: ABRAM
 */

#include "DC_Motor.h"

enum
{
	DC_idle,
	DC_busy
}DC_state_id;

unsigned int DC_speed =0;

void (*DC_state)();

void DC_INITIALIZE()
{
	printf("DC MOTOR INITIALIZED\n");

}

void DC_Motor_Speed (int speed)

{
	DC_speed =speed ;
	DC_state = STATE(DC_busy);
	printf("CA---------speed= %d-------->DC \n",DC_speed);
}


STATE_DEFINE(DC_idle)
{
	//state_Name
	DC_state_id = DC_idle ;

	//state_Action
	//call pwm to make speed = DC_speed
	//DC_Motor (speed)
	DC_speed =0 ;
	printf("DC_idle state : speed = %d \n",DC_speed);
	DC_state = STATE(DC_idle);
	//state_Name
	DC_state_id = DC_idle ;

	//state_Action
	//call pwm to make speed = DC_speed
	//DC_Motor (speed)
	DC_speed =0 ;
	printf("DC_idle state : speed = %d \n",DC_speed);
	DC_state = STATE(DC_idle);

}

STATE_DEFINE(DC_busy)
{
	//state_Name
	DC_state_id = DC_busy ;

	//state_Action
	//DC_Motor (speed)
	DC_speed =30 ;
	printf("DC_busy state : speed =%d \n",DC_speed);
	DC_state = STATE(DC_idle);

}
