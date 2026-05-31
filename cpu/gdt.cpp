#include "gdt.h"

extern "C" void gdtFlush();

struct GDTEntry
{
    unsigned short limitLow;
    unsigned short baseLow;
    unsigned char baseMiddle;
    unsigned char access;
    unsigned char granularity;
    unsigned char baseHigh;
} __attribute__((packed));

struct GDTPointer
{
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));

GDTEntry gdt[3];
GDTPointer gdtPtr;

static void setGDTEntry(
    int num,
    unsigned int base,
    unsigned int limit,
    unsigned char access,
    unsigned char granularity)
{
    gdt[num].baseLow = (base & 0xFFFF);
    gdt[num].baseMiddle = (base >> 16) & 0xFF;
    gdt[num].baseHigh = (base >> 24) & 0xFF;

    gdt[num].limitLow = (limit & 0xFFFF);
    gdt[num].granularity = (limit >> 16) & 0x0F;

    gdt[num].granularity |= granularity & 0xF0;
    gdt[num].access = access;
}

extern "C" void loadGDT()
{
    gdtPtr.limit =
        (sizeof(GDTEntry) * 3) - 1;

    gdtPtr.base = (unsigned int)&gdt;

    setGDTEntry(0, 0, 0, 0, 0);

    setGDTEntry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);

    setGDTEntry(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

    asm volatile("lgdt (%0)" : : "r"(&gdtPtr));

    gdtFlush();
}