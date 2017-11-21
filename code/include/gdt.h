#ifndef _GDT_H
#define _GDT_H

// http://stackoverflow.com/questions/34243432/how-are-ldt-and-gdt-used-differently-in-intel-x86

#include <types.h>

class GlobalDescriptorTable
{
public:
    class GlobalDescriptorTableSegment
    {
    private:
        uint16_t limit_lo;
        uint16_t base_lo;
        uint8_t base_hi;
        uint8_t type;
        uint8_t limit_hi;
        uint8_t base_vhi;

    public:
        GlobalDescriptorTableSegment(uint32_t base, uint32_t limit, uint8_t type);
        uint32_t getBase();
        uint32_t getLimit();
    }__attribute__((packed));

private:
    GlobalDescriptorTableSegment nullSegment;
    GlobalDescriptorTableSegment unusedSegment;
    GlobalDescriptorTableSegment codeSegment;
    GlobalDescriptorTableSegment dataSegment;

public:

    GlobalDescriptorTable();
    ~GlobalDescriptorTable();

    uint16_t getCodeSegment();
    uint16_t getDataSegment();
};

#endif /*_GDT_H*/
