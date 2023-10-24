/*
 * MEMORY_MAP.h
 *
 * Created: 10/17/2023 8:08:26 PM
 *  Author: ABRAM
 */ 


#ifndef MEMORY_MAP_H_
#define MEMORY_MAP_H_



#define IO_BASE 0x20
#define PORTA *(volatile unsigned int *)(IO_BASE+0x1B)
#define DDRA  *(volatile unsigned int *)(IO_BASE+0x1A)
#define PINA  *(volatile unsigned int *)(IO_BASE+0x19)

#define PORTB *(volatile unsigned int *)(IO_BASE+ 0x18)
#define DDRB  *(volatile unsigned int *)(IO_BASE+ 0x17)
#define PINB *(volatile unsigned int *)(IO_BASE+ 0x16)

#define PORTC *(volatile unsigned int *)(IO_BASE+ 0x15)
#define DDRC  *(volatile unsigned int *)(IO_BASE+ 0x14)
#define PINC  *(volatile unsigned int *)(IO_BASE+ 0x13)

#define PORTD *(volatile unsigned int *)(IO_BASE+ 0x12)
#define DDRD  *(volatile unsigned int *)(IO_BASE+ 0x11)
#define PIND  *(volatile unsigned int *)(IO_BASE+ 0x10)



#endif /* MEMORY_MAP_H_ */