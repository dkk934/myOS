#pragma once

extern unsigned short* videoMemory;
extern int cursorX;
extern int cursorY;

void clearScreen();
void print(const char* str);
void printChar(char c);