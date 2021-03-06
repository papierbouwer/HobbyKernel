#include <hardware/ports.h>
#include <types.h>

Port::Port(uint16_t portnumber)
{
    this->portnumber = portnumber;
}

Port::~Port(){}

Port8Bit::Port8Bit(uint16_t portnumber)
    : Port(portnumber)
{
}

Port8Bit::~Port8Bit(){}

void Port8Bit::write(uint8_t data)
{
    write8(portnumber, data);
}

uint8_t Port8Bit::read()
{
    return read8(portnumber);
}

Port8BitSlow::Port8BitSlow(uint16_t portnumber)
    : Port8Bit(portnumber)
{
}

Port8BitSlow::~Port8BitSlow(){}

void Port8BitSlow::write(uint8_t data)
{
    write8Slow(portnumber, data);
}

Port16Bit::Port16Bit(uint16_t portnumber)
    : Port(portnumber)
{
}

Port16Bit::~Port16Bit(){}

void Port16Bit::write(uint16_t data)
{
    write16(portnumber, data);
}

uint16_t Port16Bit::read()
{
    return read16(portnumber);
}

Port32Bit::Port32Bit(uint16_t portnumber)
    : Port(portnumber)
{
}

Port32Bit::~Port32Bit(){}

void Port32Bit::write(uint32_t data)
{
    write32(portnumber, data);
}

uint32_t Port32Bit::read()
{
    return read32(portnumber);
}
