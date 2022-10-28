/*
 * DC.h
 *
 *  Created on: Oct 21, 2022
 *      Author: ABRAM
 */

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#include "State.h"



void DC_INITIALIZE();
STATE_DEFINE(DC_idle);
STATE_DEFINE(DC_busy);

//global pointer to function
extern void (*DC_state)();
#endif /* DC_MOTOR_H_ */
