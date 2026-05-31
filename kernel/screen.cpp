#include "screen.h"

unsigned short* videoMemory = (unsigned short*)0xB8000;

int cursorX = 0;
int cursorY = 0;

static const int VGA_WIDTH = 80;
static const int VGA_HEIGHT = 25;
static const int VGA_COLOR = 0x02; // Green text on black background

void clearScreen()
{
    for (int y = 0; y < VGA_HEIGHT; y++)
    {
        for (int x = 0; x < VGA_WIDTH; x++)
        {
            videoMemory[y * VGA_WIDTH + x] = (VGA_COLOR << 8) | ' ';
        }
    }

    cursorX = 0;
    cursorY = 0;
}

void printChar(char c)
{
    if (c == '\n')
    {
        cursorX = 0;
        cursorY++;

        if (cursorY >= VGA_HEIGHT)
        {
            cursorY = 0;
        }

        return;
    }

    videoMemory[cursorY * VGA_WIDTH + cursorX] =
        (VGA_COLOR << 8) | c;

    cursorX++;

    if (cursorX >= VGA_WIDTH)
    {
        cursorX = 0;
        cursorY++;
    }

    if (cursorY >= VGA_HEIGHT)
    {
        cursorY = 0;
    }
}

void print(const char* str)
{
    int i = 0;

    while (str[i] != '\0')
    {
        printChar(str[i]);
        i++;
    }
}