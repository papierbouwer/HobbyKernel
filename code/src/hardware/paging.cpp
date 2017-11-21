#include <types.h>
#include <hardware/paging.h>

uint32_t Page_Table1[1024 * 1024];
uint32_t Page_Directory[1024 * 1];

void enablePaging()
{
    char* vidmem = (char*) 0xb8000;
    //asm(".intel_syntax noprefix");
    uint32_t PhysicalAddressAndFlags = 7;
    vidmem[0] = 'a';
	for(uint32_t index = 0; index < SIZE_OF_PAGE_TABLES; index++)
	{
		Page_Table1[index] = PhysicalAddressAndFlags;
		PhysicalAddressAndFlags += 4096;
	}

    vidmem[0] = 'b';
	PhysicalAddressAndFlags = (uint32_t)&Page_Table1[0];
	// or EBX, 7		; 0b111 - Setting Page Directory flags (Present: ON, Read/Write: ON, User/Supervisor: ON)
	PhysicalAddressAndFlags |= 7;
    vidmem[0] = 'c';
	for(int index = 0; index < NUMBER_OF_ENTRIES_PER_PAGE_DIRECTORY; index++)
	{
		Page_Directory[index] = PhysicalAddressAndFlags;
    	PhysicalAddressAndFlags += 4096;
	}
    vidmem[0] = 'd';
	/* ; 2. Set page directory
	   ; 		This requires us to load the physical address of the page directory
	   ; 		then move it into CR3
	   lea ECX, [Page_Directory]
	   mov CR3, ECX */

	   __asm__
	   (
			"lea (Page_Directory), %ECX \n"
			"mov %ECX, %CR3\n"
	   );
       vidmem[0] = 'e';
	/* 3. Switch on paging
	; 		This requires us to enable paging by setting CR0
	   mov ECX, CR0
	   or ECX, 0x80000000   ; Set PG bit in CR0 to enable paging.
	   mov CR0, ECX*/

	   __asm__
	   (
			"mov %CR0, %ECX\n"
			"or $0x80000000, %ECX\n"
			"mov %ECX, %CR0\n"
	   );
       vidmem[0] = 'f';
    // END - Set Virtual Memory
    //asm(".att_syntax prefix");
}
