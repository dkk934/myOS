[BITS 32]

section .multiboot
align 4

dd 0x1BADB002
dd 0x00
dd -(0x1BADB002)

section .bss

align 16
stack_bottom:
    resb 16384
stack_top:

section .text
global _start

extern kernel_main
extern loadGDT

_start:

    cli

    mov esp, stack_top

    call loadGDT

    call kernel_main

hang:
    hlt
    jmp hang