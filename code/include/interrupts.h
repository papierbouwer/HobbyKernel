#ifndef _INTERRUPTS_H
#define _INTERRUPTS_H

#include <types.h>
#include <hardware/ports.h>
#include <gdt.h>

class InterruptDescriptionTable
{
protected:
    struct InterruptDescriptionTableSegment
    {
        uint16_t handlerAdressLow;
        uint16_t codeSegmentSelector;
        uint8_t zeroBlock;
        uint8_t accessType;
        uint16_t handlerAdressHigh;
    }__attribute__((packed));

    struct InterruptDescriptionTablePointer
    {
        uint16_t size;
        uint16_t base;
    }__attribute__((packed));

    static InterruptDescriptionTableSegment interruptDescriptionTable[256];

    uint16_t hardwareInterruptOffset;

    static void setInterruptDescriptorTableEntry(
        uint8_t interrupt,
        uint16_t codeSegmentSelectorOffset,
        void (*handler)(),
        uint8_t descriptorPrivilegeLevel,
        uint8_t descriptorType
    );

    static void HandleInterruptRequest0x00();
    static void HandleInterruptRequest0x01();
    static void HandleInterruptRequest0x02();
    static void HandleInterruptRequest0x03();
    static void HandleInterruptRequest0x04();
    static void HandleInterruptRequest0x05();
    static void HandleInterruptRequest0x06();
    static void HandleInterruptRequest0x07();
    static void HandleInterruptRequest0x08();
    static void HandleInterruptRequest0x09();
    static void HandleInterruptRequest0x0A();
    static void HandleInterruptRequest0x0B();
    static void HandleInterruptRequest0x0C();
    static void HandleInterruptRequest0x0D();
    static void HandleInterruptRequest0x0E();
    static void HandleInterruptRequest0x0F();
    static void HandleInterruptRequest0x31();

    static void HandleException0x00();
    static void HandleException0x01();
    static void HandleException0x02();
    static void HandleException0x03();
    static void HandleException0x04();
    static void HandleException0x05();
    static void HandleException0x06();
    static void HandleException0x07();
    static void HandleException0x08();
    static void HandleException0x09();
    static void HandleException0x0A();
    static void HandleException0x0B();
    static void HandleException0x0C();
    static void HandleException0x0D();
    static void HandleException0x0E();
    static void HandleException0x0F();
    static void HandleException0x10();
    static void HandleException0x11();
    static void HandleException0x12();
    static void HandleException0x13();

    static void InterruptIgnore();

    static uint32_t handleInterrupt(uint8_t interrupt, uint32_t esp);

    Port8BitSlow programmableInterruptControllerMasterCommandPort;
    Port8BitSlow programmableInterruptControllerMasterDataPort;
    Port8BitSlow programmableInterruptControllerSlaveCommandPort;
    Port8BitSlow programmableInterruptControllerSlaveDataPort;
public:
    InterruptDescriptionTable(uint16_t hardwareInterruptOffset, GlobalDescriptorTable* globalDescriptorTable);
    ~InterruptDescriptionTable();
    uint16_t getHardwareInterruptOffset();
    void activate();
    void deactivate();
};

#endif /*_INTERRUPTS_H*/
