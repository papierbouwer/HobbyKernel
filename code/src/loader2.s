.set MAGIC, 0x1badb002
.set FLAGS, (1<<0 | 1<<1)
.set CHECKSUM, -(MAGIC + FLAGS)
.set GRAPHICS_VBE_MODE_INFO, 0x7fffffff
.set GRAPHICS_VBE_CONTROL_INFO, 0x7fffffff
.set GRAPHICS_VBE_MODE, 0x7fffffff

.section .multiboot
    .long MAGIC
    .long FLAGS
    .long CHECKSUM

.section .text
.extern kmain
.extern callConstructors
.global loader


loader:
    # Put the processor in protected mode
    mov %cr0, %ecx
    or $0x00000001, %ecx
    mov %ecx, %cr0

    cli

    mov $kernel_stack, %esp # Set the stack pointer to the defined stack area to make opps like push and pop possible
    # Test if the kernel is loaded by a multiboot compatible loader
    mov $0x2badb002, %ecx
    cmp %ecx, %eax

    # If not, go to an other label
    jne _notvalidloader

    # If so, continue with calling all the constructors for static objects,
    call callConstructors

    # push the multiboot number and the multiboot header
    push %eax
    push %ebx

    call kmain # and call the main C++ kernel function to start execution in C++

_stop:
    cli
    hlt
    jmp _stop

_notvalidloader:
    # print an error message and go to _stop
    movb $'n', (0xb8000)
    movb $'o', (0xb8002)
    movb $' ', (0xb8004)
    movb $'v', (0xb8006)
    movb $'a', (0xb8008)
    movb $'l', (0xb800a)
    movb $'i', (0xb800c)
    movb $'d', (0xb800e)
    movb $' ', (0xb8010)
    movb $'b', (0xb8012)
    movb $'o', (0xb8014)
    movb $'o', (0xb8016)
    movb $'t', (0xb8018)
    movb $'!', (0xb801a)

    jmp _stop

.section .bss
.space 2*1024*1024; # 2 MiB
kernel_stack:
