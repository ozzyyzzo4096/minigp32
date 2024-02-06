
@********************************************************************
@* crt0.s - startup code for arm-elf-gcc v0.2 (w) Groepaz/Hitmen
@* Target CPU: Arm/T9  Machine: GamePark GP32
@********************************************************************

@  .include "../include/gp32.inc"

    .GLOBAL     _start
    .GLOBAL     atexit

    .EXTERN     main    @ user entry point

    .global     start_vector

    .section ".text"
    .align 4
    .code  32

_start:
        b start_vector

        @ .text start+.rodata end

          .word 0x0c000000      @ Start of ROM code
          .word _romdata        @ End of ROM code (=start of ROM data)

        @ .data start/end

          .word _bdata          @ Base of RAM to initialize (=start of RAM data)
          .word _edata

        @ .bss start/end

          .word _bstart         @ Base of RAM to Zero Out
          .word _bend

        @ some weirdo sequence ?! ;=P

        .word 0x44450011

        .word 0x01234567
        .word 0x12345678
        .word 0x23456789
        .word 0x34567890
        .word 0x45678901
        .word 0x56789012
        .word 0x23456789
        .word 0x34567890
        .word 0x45678901
        .word 0x56789012
        .word 0x23456789
        .word 0x34567890
        .word 0x45678901
        .word 0x56789012

@    .ALIGN  4
@    .CODE   32

start_vector:

        bl       main @ jump to entry point

@ dummy restart function

_end:
        ldr lr,=0x00000000

@ dummy function to keep gcc happy

atexit:
         mov pc,lr

        .END


