
#include <interrupts.h>
#include <types.h>
#include <hardware/ports.h>
#include <screen.h>

/*
 *
 *struct InterruptDescriptionTableSegment
 *{
 *    uint16_t handlerAdressLow;
 *    uint16_t codeSegmentSelector;
 *    uint8_t zeroBlock;
 *    uint8_t accessType;
 *    uint16_t handlerAdressHigh;
 *}__attribute__((packed));
 *
*/

InterruptDescriptionTable::InterruptDescriptionTableSegment InterruptDescriptionTable::interruptDescriptionTable[256];

void InterruptDescriptionTable::setInterruptDescriptorTableEntry(
    uint8_t interrupt,
    uint16_t codeSegmentSelectorOffset,
    void (*handler)(),
    uint8_t descriptorPrivilegeLevel,
    uint8_t descriptorType
)
{
    interruptDescriptionTable[interrupt].handlerAdressLow = ((uint32_t) handler) & 0xFFFF;
    interruptDescriptionTable[interrupt].handlerAdressHigh = ((uint32_t) handler >> 16) & 0xFFFF;
    interruptDescriptionTable[interrupt].zeroBlock = 0;
    interruptDescriptionTable[interrupt].codeSegmentSelector = codeSegmentSelectorOffset;

    const uint8_t IDT_DESC_PRESENT = 0x80;
    interruptDescriptionTable[interrupt].accessType = IDT_DESC_PRESENT | ((descriptorPrivilegeLevel & 3) << 5) | descriptorType;
}

uint32_t InterruptDescriptionTable::handleInterrupt(uint8_t interrupt, uint32_t esp)
{
    char* foo = "0x00";
    char* hex = "0123456789ABCDEF";
    Screen screen;

    foo[2] = hex[(interrupt >> 4) & 0xF];
    foo[3] = hex[interrupt & 0xF];
    char* vid = (char *) 0xb8000;
    vid[0] = foo[0];
    vid[2] = foo[1];
    vid[4] = foo[2];
    vid[6] = foo[3];

    return esp;
}

InterruptDescriptionTable::InterruptDescriptionTable(
    uint16_t hardwareInterruptOffset,
    GlobalDescriptorTable* globalDescriptorTable
)
: programmableInterruptControllerMasterCommandPort(0x20),
  programmableInterruptControllerMasterDataPort(0x21),
  programmableInterruptControllerSlaveCommandPort(0xA0),
  programmableInterruptControllerSlaveDataPort(0xA1)
{
    this->hardwareInterruptOffset = hardwareInterruptOffset;
    uint32_t codeSegment = globalDescriptorTable->getCodeSegment();

    const uint8_t IDT_INTERRUPT_GATE = 0xE;
    for(uint8_t i = 255; i > 0; i--)
    {
        setInterruptDescriptorTableEntry(i, codeSegment, &InterruptIgnore, 0, IDT_INTERRUPT_GATE);
    }

    setInterruptDescriptorTableEntry(0, codeSegment, &InterruptIgnore, 0, IDT_INTERRUPT_GATE);
    //handlers[0] = 0;

    setInterruptDescriptorTableEntry(0x00, codeSegment, &HandleException0x00, 0, IDT_INTERRUPT_GATE);
    setInterruptDescriptorTableEntry(0x01, codeSegment, &HandleException0x01, 0, IDT_INTERRUPT_GATE);
    setInterruptDescriptorTableEntry(0x02, codeSegment, &HandleException0x02, 0, IDT_INTERRUPT_GATE);
    setInterruptDescriptorTableEntry(0x03, codeSegment, &HandleException0x03, 0, IDT_INTERRUPT_GATE);
    setInterruptDescriptorTableEntry(0x04, codeSegment, &HandleException0x04, 0, IDT_INTERRUPT_GATE);
    setInterruptDescriptorTableEntry(0x05, codeSegment, &HandleException0x05, 0, IDT_INTERRUPT_GATE);
    setInterruptDescriptorTableEntry(0x06, codeSegment, &HandleException0x06, 0, IDT_INTERRUPT_GATE);
    setInterruptDescriptorTableEntry(0x07, codeSegment, &HandleException0x07, 0, IDT_INTERRUPT_GATE);
    setInterruptDescriptorTableEntry(0x08, codeSegment, &HandleException0x08, 0, IDT_INTERRUPT_GATE);
    setInterruptDescriptorTableEntry(0x09, codeSegment, &HandleException0x09, 0, IDT_INTERRUPT_GATE);
    setInterruptDescriptorTableEntry(0x0A, codeSegment, &HandleException0x0A, 0, IDT_INTERRUPT_GATE);
    setInterruptDescriptorTableEntry(0x0B, codeSegment, &HandleException0x0B, 0, IDT_INTERRUPT_GATE);
    setInterruptDescriptorTableEntry(0x0C, codeSegment, &HandleException0x0C, 0, IDT_INTERRUPT_GATE);
    setInterruptDescriptorTableEntry(0x0D, codeSegment, &HandleException0x0D, 0, IDT_INTERRUPT_GATE);
    setInterruptDescriptorTableEntry(0x0E, codeSegment, &HandleException0x0E, 0, IDT_INTERRUPT_GATE);
    setInterruptDescriptorTableEntry(0x0F, codeSegment, &HandleException0x0F, 0, IDT_INTERRUPT_GATE);
    setInterruptDescriptorTableEntry(0x10, codeSegment, &HandleException0x10, 0, IDT_INTERRUPT_GATE);
    setInterruptDescriptorTableEntry(0x11, codeSegment, &HandleException0x11, 0, IDT_INTERRUPT_GATE);
    setInterruptDescriptorTableEntry(0x12, codeSegment, &HandleException0x12, 0, IDT_INTERRUPT_GATE);
    setInterruptDescriptorTableEntry(0x13, codeSegment, &HandleException0x13, 0, IDT_INTERRUPT_GATE);

    setInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x00, codeSegment, &HandleInterruptRequest0x00, 0, IDT_INTERRUPT_GATE);
    setInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x01, codeSegment, &HandleInterruptRequest0x01, 0, IDT_INTERRUPT_GATE);
    setInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x02, codeSegment, &HandleInterruptRequest0x02, 0, IDT_INTERRUPT_GATE);
    setInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x03, codeSegment, &HandleInterruptRequest0x03, 0, IDT_INTERRUPT_GATE);
    setInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x04, codeSegment, &HandleInterruptRequest0x04, 0, IDT_INTERRUPT_GATE);
    setInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x05, codeSegment, &HandleInterruptRequest0x05, 0, IDT_INTERRUPT_GATE);
    setInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x06, codeSegment, &HandleInterruptRequest0x06, 0, IDT_INTERRUPT_GATE);
    setInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x07, codeSegment, &HandleInterruptRequest0x07, 0, IDT_INTERRUPT_GATE);
    setInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x08, codeSegment, &HandleInterruptRequest0x08, 0, IDT_INTERRUPT_GATE);
    setInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x09, codeSegment, &HandleInterruptRequest0x09, 0, IDT_INTERRUPT_GATE);
    setInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x0A, codeSegment, &HandleInterruptRequest0x0A, 0, IDT_INTERRUPT_GATE);
    setInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x0B, codeSegment, &HandleInterruptRequest0x0B, 0, IDT_INTERRUPT_GATE);
    setInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x0C, codeSegment, &HandleInterruptRequest0x0C, 0, IDT_INTERRUPT_GATE);
    setInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x0D, codeSegment, &HandleInterruptRequest0x0D, 0, IDT_INTERRUPT_GATE);
    setInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x0E, codeSegment, &HandleInterruptRequest0x0E, 0, IDT_INTERRUPT_GATE);
    setInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x0F, codeSegment, &HandleInterruptRequest0x0F, 0, IDT_INTERRUPT_GATE);

    programmableInterruptControllerMasterCommandPort.write(0x11);
    programmableInterruptControllerSlaveCommandPort.write(0x11);

    programmableInterruptControllerMasterDataPort.write(hardwareInterruptOffset);
    programmableInterruptControllerSlaveDataPort.write(hardwareInterruptOffset+8);

    programmableInterruptControllerMasterDataPort.write(0x04);
    programmableInterruptControllerSlaveDataPort.write(0x02);

    programmableInterruptControllerMasterDataPort.write(0x01);
    programmableInterruptControllerSlaveDataPort.write(0x01);

    programmableInterruptControllerMasterDataPort.write(0x00);
    programmableInterruptControllerSlaveDataPort.write(0x00);

    InterruptDescriptionTablePointer interruptDescriptionTablePointer;
    interruptDescriptionTablePointer.size = 256*sizeof(InterruptDescriptionTableSegment) - 1;
    interruptDescriptionTablePointer.base = (uint32_t) interruptDescriptionTable;

    asm volatile("lidt %0" : : "m" (interruptDescriptionTablePointer));
}

InterruptDescriptionTable::~InterruptDescriptionTable()
{
    deactivate();
}

void InterruptDescriptionTable::activate()
{
    asm("sti");
}

void InterruptDescriptionTable::deactivate()
{
    //asm("cli");
}

uint16_t InterruptDescriptionTable::getHardwareInterruptOffset()
{
    return hardwareInterruptOffset;
}
