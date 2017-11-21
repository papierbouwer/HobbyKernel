#ifndef _SCREEN_H
#define _SCREEN_H

#include <types.h>
#include <hardware/ports.h>

class Screen
{
private:
    void printch(char c);
    #define SW 80
    #define SH 25
    #define SD 2
    #define COLOR 0x0F

    uint8_t cursorX, cursorY;
    char* vidmem = (char*) 0xb8000;
    void clearLine(uint8_t from,uint8_t to);
    void updateCursor();
    void newLineCheck();
public:
    void printHex8(uint8_t number);
    void printHex16(uint16_t number);
    void printHex32(uint32_t number);
    void printHex64(uint64_t number);
    
    void clearScreen();
    void scrollUp(uint8_t lineNumber);
    void print (char* ch);
    Screen();
    ~Screen();

    uint16_t strlength(char* ch);
};

#endif /*_SCREEN_H*/
