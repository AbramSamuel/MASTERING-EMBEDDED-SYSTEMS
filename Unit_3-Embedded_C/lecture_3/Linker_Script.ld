/* ENG. Abram Samuel */


MEMORY 
{
    flash(RX) : ORIGIN = 0x08000000 , LENGTH = 128K
    sram(RWX) : ORIGIN =0x20000000 , LENGTH = 20K
}

SECTIONS
{
    .text :
    {
        *(.vectors*)
        *(.text*)
        *(.rodata)
        _E_text = . ;
    }>flash

    .data :
    {
        _S_data = . ;
        . = ALIGN(4);
        *(.data*)
        . = ALIGN(4);
        _E_data = . ;
    }> sram  AT> flash

    .bss :
    {
        _S_bss = . ;
        *(.bss*)
        . = ALIGN(4);
        _E_bss = . ;
        . = ALIGN(4);
        . = . +0x1000;
        _stack_top = .;

    }> sram
}