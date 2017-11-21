// TODO:
// 1.  Interupts
// 2.  Toetsenbord werkend
// 3.  PCI werkend
// 4.  Naar VGA textmode
// 5.  Naar VGA Graphicsmode
// 6.  Geheugen gemanaged
// 7.  Multitasking
// 8.  HDD kunnen benaderen
// 9.  Programma's kunnen starten in usermode
// 10. Systemcalles
// 11. Netwerk
// 12. Muis werkend
// 13. seriele poort werkend
// 14. USB

#include <types.h>
#include <gdt.h>
#include <interrupts.h>
#include <screen.h>
#include <hardware/paging.h>

typedef void (*constructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;
extern "C" void callConstructors()
{
    for(constructor* i = &start_ctors; i != &end_ctors; i++)
        (*i)();
}

extern "C" void kmain(const void* multiboot_structure, uint32_t multiboot_magic)
{
    Screen screen;
    GlobalDescriptorTable globalDescriptorTable;
    //enablePaging();

    //InterruptDescriptionTable interruptDescriptionTable(0x20, &globalDescriptorTable);
    //interruptDescriptionTable.activate();
    //screen.print("Hello World!");

    //asm("int $0x01");
}
