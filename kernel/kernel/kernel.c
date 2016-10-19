#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include <kernel/common.h>
#include <kernel/multiboot.h>
#include <kernel/elf.h>
#include <kernel/gdt.h>
#include <kernel/idt.h>
#include <kernel/isr.h>
#include <kernel/tty.h>
#include <kernel/timer.h>
#include <kernel/panic.h>

elf_t kernel_elf;

void kernel_early(void)
{
	terminal_initialize();
        gdt_install();      /* Global descriptor table */
	idt_install();      /* IDT */
	isrs_install();     /* Interrupt service requests */
        irq_install();
        //init_timer((uint32_t)20);
}

int kernel_main(multiboot_t *mboot_ptr)
{
        kernel_early();
        kernel_elf = elf_from_multiboot(mboot_ptr);
        
        printf("Hello, kernel World!\n");
        asm volatile("int $0x3");
        asm volatile("int $0x4");
        //asm volatile("sti");
        panic ("Testing panic mechanism");
        return (0xdeadbeef);
}
    