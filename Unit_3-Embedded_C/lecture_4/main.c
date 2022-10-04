#include <stdint.h>

#define SYSCTL_RCGC2_R  *((volatile unsigned long *)(0x400FE108))
#define GPIO_PORTF_DIR_R *((volatile unsigned long *)(0x40025400))
#define GPIO_PORTF_DATA_R *((volatile unsigned long *)(0x400253FC))
#define GPIO_PORTF_DEN_R *((volatile unsigned long *)(0x4002551C))

int main(void)
{
   volatile unsigned long delay_counter;
    // delay to make sure the GPIOF is up to run
    for(delay_counter = 0; delay_counter <200;delay_counter++) 
    {   
    // Enable the GPIO port
    SYSCTL_RCGC2_R = 0x00000020;
    // enable the GPIO pin
    GPIO_PORTF_DEN_R |= 1<<3;
    // Set (PF3) the direction as output
    GPIO_PORTF_DIR_R |= 1<<3;
    }

    while (1)
    {
        // Enable DATA regester to turn on the led
        GPIO_PORTF_DATA_R |= 1 << 3;
        for (delay_counter = 0; delay_counter < 200000; delay_counter++);
        // Disable DATA regester to turn off the led
        GPIO_PORTF_DATA_R &= ~(1 << 3);
        for(delay_counter = 0; delay_counter < 200000; delay_counter++);
        
    }
    return 0;
    
}