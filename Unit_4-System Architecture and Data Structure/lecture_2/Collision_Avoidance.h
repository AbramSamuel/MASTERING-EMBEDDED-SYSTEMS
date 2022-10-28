/*
 * CA.h
 *
 *  Created on: Oct 20, 2022
 *      Author: ABRAM
 */

#ifndef COLLISION_AVOIDANCE_H_
#define COLLISION_AVOIDANCE_H_

#include "State.h"


//Prototypes
STATE_DEFINE(CA_WAITING);
STATE_DEFINE(CA_DRIVING);
//global pointer to function
extern void (*CA_state)();
#endif /* COLLISION_AVOIDANCE_H_ */
