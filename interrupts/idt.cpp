#include "idt.h"
#include "../kernel/io.h"
#include "../kernel/screen.h"
#include "../kernel/keyboard.h"

extern "C" void isr0();
extern "C" void loadIDT(void*);
extern "C" void isr0();
extern "C" void isr1();
extern "C" void isr2();
extern "C" void isr3();
extern "C" void isr4();
extern "C" void isr5();
extern "C" void isr6();
extern "C" void isr7();
extern "C" void isr8();
extern "C" void isr9();
extern "C" void isr10();
extern "C" void isr11();
extern "C" void isr12();
extern "C" void isr13();
extern "C" void isr14();
extern "C" void isr15();
extern "C" void isr16();
extern "C" void isr17();
extern "C" void isr18();
extern "C" void isr19();
extern "C" void isr20();
extern "C" void isr21();
extern "C" void isr22();
extern "C" void isr23();
extern "C" void isr24();
extern "C" void isr25();
extern "C" void isr26();
extern "C" void isr27();
extern "C" void isr28();
extern "C" void isr29();
extern "C" void isr30();
extern "C" void isr31();

extern "C" void irq0();
extern "C" void irq1();
extern "C" void irq2();
extern "C" void irq3();
extern "C" void irq4();
extern "C" void irq5();
extern "C" void irq6();
extern "C" void irq7();
extern "C" void irq8();
extern "C" void irq9();
extern "C" void irq10();
extern "C" void irq11();
extern "C" void irq12();
extern "C" void irq13();
extern "C" void irq14();
extern "C" void irq15();

struct IDTEntry
{
    unsigned short offsetLow;
    unsigned short selector;
    unsigned char zero;
    unsigned char typeAttr;
    unsigned short offsetHigh;
} __attribute__((packed));

struct IDTPointer
{
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));

IDTEntry idt[256];
IDTPointer idtPtr;

void setIDTGate(int n, unsigned int handler)
{
    idt[n].offsetLow = handler & 0xFFFF;
    idt[n].selector = 0x08;
    idt[n].zero = 0;
    idt[n].typeAttr = 0x8E;
    idt[n].offsetHigh =
        (handler >> 16) & 0xFFFF;
}

void remapPIC()
{
    outb(0x20, 0x11);
    outb(0xA0, 0x11);

    outb(0x21, 0x20);
    outb(0xA1, 0x28);

    outb(0x21, 0x04);
    outb(0xA1, 0x02);

    outb(0x21, 0x01);
    outb(0xA1, 0x01);

    outb(0x21, 0xFD); // 11111101
    outb(0xA1, 0xFF);
}
void initIDT()
{
    idtPtr.limit =
        sizeof(IDTEntry) * 256 - 1;

    idtPtr.base =
        (unsigned int)&idt;

    for (int i = 0; i < 256; i++)
    {
        idt[i].offsetLow = 0;
        idt[i].selector = 0;
        idt[i].zero = 0;
        idt[i].typeAttr = 0;
        idt[i].offsetHigh = 0;
    }

    setIDTGate(0,  (unsigned int)isr0);
    setIDTGate(1,  (unsigned int)isr1);
    setIDTGate(2,  (unsigned int)isr2);
    setIDTGate(3,  (unsigned int)isr3);
    setIDTGate(4,  (unsigned int)isr4);
    setIDTGate(5,  (unsigned int)isr5);
    setIDTGate(6,  (unsigned int)isr6);
    setIDTGate(7,  (unsigned int)isr7);
    setIDTGate(8,  (unsigned int)isr8);
    setIDTGate(9,  (unsigned int)isr9);
    setIDTGate(10, (unsigned int)isr10);
    setIDTGate(11, (unsigned int)isr11);
    setIDTGate(12, (unsigned int)isr12);
    setIDTGate(13, (unsigned int)isr13);
    setIDTGate(14, (unsigned int)isr14);
    setIDTGate(15, (unsigned int)isr15);
    setIDTGate(16, (unsigned int)isr16);
    setIDTGate(17, (unsigned int)isr17);
    setIDTGate(18, (unsigned int)isr18);
    setIDTGate(19, (unsigned int)isr19);
    setIDTGate(20, (unsigned int)isr20);
    setIDTGate(21, (unsigned int)isr21);
    setIDTGate(22, (unsigned int)isr22);
    setIDTGate(23, (unsigned int)isr23);
    setIDTGate(24, (unsigned int)isr24);
    setIDTGate(25, (unsigned int)isr25);
    setIDTGate(26, (unsigned int)isr26);
    setIDTGate(27, (unsigned int)isr27);
    setIDTGate(28, (unsigned int)isr28);
    setIDTGate(29, (unsigned int)isr29);
    setIDTGate(30, (unsigned int)isr30);
    setIDTGate(31, (unsigned int)isr31);

    setIDTGate(32, (unsigned int)irq0);
    setIDTGate(33, (unsigned int)irq1);
    setIDTGate(34, (unsigned int)irq2);
    setIDTGate(35, (unsigned int)irq3);
    setIDTGate(36, (unsigned int)irq4);
    setIDTGate(37, (unsigned int)irq5);
    setIDTGate(38, (unsigned int)irq6);
    setIDTGate(39, (unsigned int)irq7);
    setIDTGate(40, (unsigned int)irq8);
    setIDTGate(41, (unsigned int)irq9);
    setIDTGate(42, (unsigned int)irq10);
    setIDTGate(43, (unsigned int)irq11);
    setIDTGate(44, (unsigned int)irq12);
    setIDTGate(45, (unsigned int)irq13);
    setIDTGate(46, (unsigned int)irq14);
    setIDTGate(47, (unsigned int)irq15);

    remapPIC();
    // outb(0x21, 0xFF);
    // outb(0xA1, 0xFF);   

    loadIDT((void*)&idtPtr);
    asm volatile("sti");
}


extern "C" void loadIDT(void*);

const char* exceptionMessages[] =
{
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Overflow",
    "Bound Range Exceeded",
    "Invalid Opcode",
    "Device Not Available",
    "Double Fault",
    "Coprocessor Segment Overrun",
    "Invalid TSS",
    "Segment Not Present",
    "Stack Segment Fault",
    "General Protection Fault",
    "Page Fault",
    "Reserved",
    "x87 Floating Point",
    "Alignment Check",
    "Machine Check",
    "SIMD Floating Point",
    "Virtualization",
    "Control Protection",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Hypervisor Injection",
    "VMM Communication",
    "Security Exception",
    "Reserved"
};

extern "C" void exceptionHandler(int interruptNumber)
{
    print("\nEXCEPTION: ");
    print(exceptionMessages[interruptNumber]);
    print("\n");

    while (1)
    {
        asm volatile("hlt");
    }
}


extern "C" void irqHandler(int interruptNumber)
{
    print("\nIRQ ");

    if (interruptNumber == 32)
    {
        print("TIMER");
    }
    else if (interruptNumber == 33)
    {
        print("KEYBOARD");

        unsigned char scancode =
            inb(0x60);

        handleScancode(scancode);
    }
    else
    {
        print("OTHER");
    }

    print("\n");

    if (interruptNumber >= 40)
    {
        outb(0xA0, 0x20);
    }

    outb(0x20, 0x20);
}