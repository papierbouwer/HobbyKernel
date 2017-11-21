#include <screen.h>

void Screen::printch(char c)
{
    switch(c)
    {
        case (0x08):
                if(cursorX > 0)
                {
	                cursorX--;
                        vidmem[(cursorY * SW + cursorX)*SD]=0;	     //(0xF0 & color)
	        }
	        break;
       /* case (0x09):
                cursorX = (cursorX + 8) & ~(8 - 1);
                break;*/
        case ('\r'):
                cursorX = 0;
                break;
        case ('\n'):
                cursorX = 0;
                cursorY++;
                break;
        default:
                vidmem [((cursorY * SW + cursorX))*SD] = c;
                vidmem [((cursorY * SW + cursorX))*SD+1] = COLOR;
                cursorX++;
                break;

    }
    if(cursorX >= SW)
    {
        cursorX = 0;
        cursorY++;
    }
    updateCursor();
    newLineCheck();
}

void Screen::clearLine(uint8_t from,uint8_t to)
{
        uint16_t i = SW * from * SD;
        for(i;i<(SW*to*SD);i++)
        {
                vidmem[(i / 2)*2 + 1 ] = COLOR ;
                vidmem[(i / 2)*2 ] = 0;
        }
}

void Screen::updateCursor()
{
    unsigned temp;

    temp = cursorY * SW + cursorX;                                                      // Position = (y * width) +  x

    Port8Bit port1(0x3D4);
    Port8Bit port2(0x3D4);

    port1.write(14);
    port2.write(temp >> 8);
    port1.write(15);
    port2.write(temp);
    //outportb(0x3D4, 14);                                                                // CRT Control Register: Select Cursor Location
    //outportb(0x3D5, temp >> 8);                                                         // Send the high byte across the bus
    //outportb(0x3D4, 15);                                                                // CRT Control Register: Select Send Low byte
    //outportb(0x3D5, temp);                                                              // Send the Low byte of the cursor location
}

void Screen::newLineCheck()
{
        if(cursorY >=SH-1)
        {
                scrollUp(1);
        }
}

void Screen::clearScreen()
{
        clearLine(0,SH-1);
        cursorX = 0;
        cursorY = 0;
        updateCursor();
}

void Screen::scrollUp(uint8_t lineNumber)
{
        uint16_t i = 0;
        clearLine(0,lineNumber-1);                                            //updated
        for (i;i<SW*(SH-1)*2;i++)
        {
                vidmem[i] = vidmem[i+SW*2*lineNumber];
        }
        clearLine(SH-1-lineNumber,SH-1);
        if((cursorY - lineNumber) < 0 )
        {
                cursorY = 0;
                cursorX = 0;
        }
        else
        {
                cursorY -= lineNumber;
        }
        updateCursor();
}

void Screen::print(char* ch)
{
        uint16_t i = 0;
        uint8_t length = strlength(ch);              //Updated (Now we store string length on a variable to call the function only once)
        for(i;i<length;i++)
        {
                printch(ch[i]);
        }
       /* while((ch[i] != (char)0) && (i<=length))
                print(ch[i++]);*/

}


Screen::Screen()
{
    vidmem = (char*) 0xb8000;
    cursorX = 0;
    cursorY = 0;
}

Screen::~Screen(){}

uint16_t Screen::strlength(char* ch)
{
        uint16_t i = 0;           //Changed counter to 0
        while(ch[i++]);
        return i-1;               //Changed counter to i instead of i--
}

void Screen::printHex8(uint8_t number)
{
    char* foo = "0x00\n";
    char* hex = "0123456789ABCDEF";

    foo[2] = hex[(number >> 4) & 0xF];
    foo[3] = hex[number & 0xF];

    print(foo);
}

void Screen::printHex16(uint16_t number)
{
    char* foo = "0x0000\n";
    char* hex = "0123456789ABCDEF";

    foo[2] = hex[(number >> 12) & 0xF];
    foo[3] = hex[(number >> 8) & 0xF];
    foo[4] = hex[(number >> 4) & 0xF];
    foo[5] = hex[number & 0xF];

    print(foo);
}

void Screen::printHex32(uint32_t number)
{
    char* foo = "0x00000000\n";
    char* hex = "0123456789ABCDEF";

    foo[2] = hex[(number >> 28) & 0xF];
    foo[3] = hex[(number >> 24) & 0xF];
    foo[4] = hex[(number >> 20) & 0xF];
    foo[5] = hex[(number >> 16) & 0xF];
    foo[6] = hex[(number >> 12) & 0xF];
    foo[7] = hex[(number >> 8) & 0xF];
    foo[8] = hex[(number >> 4) & 0xF];
    foo[9] = hex[number & 0xF];

    print(foo);
}

void Screen::printHex64(uint64_t number)
{
    char* foo = "0x0000000000000000\n";
    char* hex = "0123456789ABCDEF";

    foo[2] = hex[(number >> 60) & 0xF];
    foo[3] = hex[(number >> 56) & 0xF];
    foo[4] = hex[(number >> 52) & 0xF];
    foo[5] = hex[(number >> 48) & 0xF];
    foo[6] = hex[(number >> 44) & 0xF];
    foo[7] = hex[(number >> 40) & 0xF];
    foo[8] = hex[(number >> 36) & 0xF];
    foo[9] = hex[(number >> 32) & 0xF];
    foo[10] = hex[(number >> 28) & 0xF];
    foo[11] = hex[(number >> 24) & 0xF];
    foo[12] = hex[(number >> 20) & 0xF];
    foo[13] = hex[(number >> 16) & 0xF];
    foo[14] = hex[(number >> 12) & 0xF];
    foo[15] = hex[(number >> 8) & 0xF];
    foo[16] = hex[(number >> 4) & 0xF];
    foo[17] = hex[number & 0xF];

    print(foo);
}
