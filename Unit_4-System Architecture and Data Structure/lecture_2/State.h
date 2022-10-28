/*
 * state.h
 *
 *  Created on: Oct 21, 2022
 *      Author: ABRAM
 */

#ifndef STATE_H_
#define STATE_H_


#define STATE_DEFINE(_StateFunc_)  void ST_##_StateFunc_()
#define STATE(_StateFunc_)   ST_##_StateFunc_


#include "stdio.h"
#include "stdlib.h"


//state connection

void US_Get_Distance(int distance);
void DC_Motor_Speed (int speed);

#endif /* STATE_H_ */
