/*
 * UTILITIES.h
 *
 * Created: 10/17/2023 8:07:04 PM
 *  Author: ABRAM
 */ 


#ifndef UTILITIES_H_
#define UTILITIES_H_



#define SETBIT(address,bit)		address |=(1<<bit)
#define CLEARBIT(address,bit)	address &= ~(1<<bit)
#define TOGGLEBIT(address,bit)  address ^=(1<<bit)
#define READBIT(address,bit)	((address>>bit)&1)



#endif /* UTILITIES_H_ */