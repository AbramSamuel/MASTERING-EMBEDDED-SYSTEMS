@ Learn-in-Depth
@ Unit 2 lesson 3
@ Mastering Embedded Systems
@ Eng.Abram Samuel

.section .vectors

.word 0x20001000              @stack top address
.word _reset                  @1 reset
.word Vector_handler          @2 NMI
.word Vector_handler          @3 Hard Fault
.word Vector_handler          @4 MM
.word Vector_handler          @5 Bus Fault
.word Vector_handler          @6 Usage Fault
.word Vector_handler          @7 RESERVED
.word Vector_handler          @8 RESERVED
.word Vector_handler          @9 RESERVED
.word Vector_handler          @10 RESERVED
.word Vector_handler          @11 SV call
.word Vector_handler          @12 Debug Reserved
.word Vector_handler          @13 RESERVED
.word Vector_handler          @14 PendSV
.word Vector_handler          @15 SysTick
.word Vector_handler          @16 IRQ0
.word Vector_handler          @17 IRQ1
.word Vector_handler          @18 IRQ2
.word Vector_handler

.section .text
_reset:
    bl main
    b .

.thumb_func

Vector_handler:
   b _reset
