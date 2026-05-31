#include "screen.h"
#include "../interrupts/idt.h"
#include "keyboard.h"
#include "../cpu/gdt.h"

extern "C" void kernel_main()
{
    clearScreen();

    print("[OK] Screen\n");

    loadGDT();
    print("[OK] GDT\n");

    initIDT();
    print("[OK] IDT\n");

    print("[OK] Enter Main Loop\n");

    while(1)
    {
        char c = getKey();

        if(c)
        {
            printChar(c);
        }

        asm volatile("hlt");
    }
}