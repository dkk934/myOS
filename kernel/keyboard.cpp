#include "keyboard.h"

static char keyboardBuffer[256];

static int bufferHead = 0;
static int bufferTail = 0;

static char scancodeTable[128] =
{
    0,
    27,
    '1','2','3','4','5','6','7','8','9','0',
    '-','=',
    '\b',
    '\t',

    'q','w','e','r','t','y','u','i','o','p',
    '[',']',

    '\n',

    0,

    'a','s','d','f','g','h','j','k','l',
    ';','\'',

    '`',

    0,

    '\\',

    'z','x','c','v','b','n','m',
    ',', '.', '/',

    0,
    '*',

    0,

    ' ',

};

static void pushKey(char c)
{
    keyboardBuffer[bufferTail] = c;

    bufferTail =
        (bufferTail + 1) % 256;
}

char getKey()
{
    if (bufferHead == bufferTail)
    {
        return 0;
    }

    char c = keyboardBuffer[bufferHead];

    bufferHead =
        (bufferHead + 1) % 256;

    return c;
}

void handleScancode(unsigned char scancode)
{
    if (scancode & 0x80)
    {
        return;
    }

    char c = scancodeTable[scancode];

    if (c)
    {
        pushKey(c);
    }
}
