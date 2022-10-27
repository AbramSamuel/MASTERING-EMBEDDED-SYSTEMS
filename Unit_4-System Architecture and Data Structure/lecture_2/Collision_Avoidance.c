/*
 * CA.c
 *
 *  Created on: Oct 20, 2022
 *      Author: ABRAM
 */

#include "Collision_Avoidance.h"


//define states

enum
{
	CA_WAITING,
	CA_DRIVING
}CA_state_id;

//variables --hidden
int CA_speed =0 ;
int CA_distance =0 ;
int CA_threshold =50 ;

//state pointer to function
void (*CA_state)();

void US_Get_Distance(int distance)
{
	CA_distance = distance;
	(CA_distance <= CA_threshold)? (CA_state =STATE(CA_WAITING)) : (CA_state =STATE(CA_DRIVING));
	printf("US---------distance= %d-------->CA \n",CA_distance);

}

STATE_DEFINE(CA_WAITING)
{
	//state_Name
	CA_state_id = CA_WAITING ;
	CA_speed =0 ;
	printf("Collision Waiting state: distance = %d speed = %d \n",CA_distance ,CA_speed);

	//state_Action
	//DC_Motor (speed)

	DC_Motor_Speed(CA_speed);


}
STATE_DEFINE(CA_DRIVING)
{
	//state_Name
	CA_state_id = CA_DRIVING;
	printf("Collision Avoidance Driving state : distance =%d speed =%d \n",CA_distance ,CA_speed);

	//state_Action
	//DC_Motor (speed)
	CA_speed =30 ;
	DC_Motor_Speed(CA_speed);

}
