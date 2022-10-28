/*
 * US.h
 *
 *  Created on: Oct 21, 2022
 *      Author: ABRAM
 */

#ifndef US_SENSOR_H_
#define US_SENSOR_H_

#include "State.h"



//prototypes
void US_INITIALIZE();
STATE_DEFINE(US_busy);

//global pointer to function
extern void (*US_state)();



#endif /* US_SENSOR_H_ */
