

// ENG.Abram Samuel

#include <stdint.h>


extern int main(void);
void Reset_Handler(void);

void Default_Handler()
{
    Reset_Handler();
}

void NMI_Handler(void) __attribute__ ((weak, alias ("Default_Handler")));
void H_fault_Handler(void) __attribute__ ((weak, alias ("Default_Handler")));
void MM_Fault_Handler(void) __attribute__ ((weak, alias ("Default_Handler")));
void Bus_Handler(void) __attribute__ ((weak, alias ("Default_Handler")));
void Usage_Fault_Handler(void) __attribute__ ((weak, alias ("Default_Handler")));

extern unsigned int _stack_top;
    uint32_t vectors[] __attribute__((section(".vectors"))) =
        {
            (uint32_t)&_stack_top,
            (uint32_t)&Reset_Handler,
            (uint32_t)&NMI_Handler,
            (uint32_t)&H_fault_Handler,
            (uint32_t)&MM_Fault_Handler,
            (uint32_t)&Bus_Handler,
            (uint32_t)&Usage_Fault_Handler

};

extern unsigned int _S_data;
extern unsigned int _E_data;
extern unsigned int _S_bss;
extern unsigned int _E_bss;
extern unsigned int _E_text;
void Reset_Handler(void)
{
    unsigned int i ;
        // copy data from flash memory to ram memory
    unsigned int data_size = (unsigned char *)& _E_data - (unsigned char *)& _S_data;
    unsigned char *P_src = (unsigned char *)& _E_text;
    unsigned char* P_dst = (unsigned char*)& _S_data;

    for ( i= 0; i < data_size; i++)
    {
        *((unsigned char*)P_dst++) = *((unsigned char*)P_src++);
    }

    // initialize .bss section with 0
    unsigned int bss_size =(unsigned char*)&_S_bss - (unsigned char*)&_E_bss;
    for( i= 0; i < bss_size; i++)
        *((unsigned char *)P_dst++) = (unsigned char)0;

    // jump to main

    main();
}