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
#include <kernel/pmm.h>
#include <kernel/vmm.h>
#include <printk.h>

elf_t kernel_elf;

void kernel_early(multiboot_t* mboot_ptr)
{
        printk(" + Initializing TTY1\n");
        terminal_initialize();
        printk(" + Initializing Global descriptor table\n");
        gdt_install();      /* Global descriptor table */
        printk(" + Initializing Interrupt descriptor table\n");
	idt_install();      /* IDT */
        printk(" + Initializing Interrupt service requests\n");
	isrs_install();     /* Interrupt service requests */
        printk(" + Initializing IRQs\n");
        irq_install();
        //printk(" - Initializing TTY1\n");
        //init_timer((uint32_t)20);
        printk(" + Initializing physical memory manager\n");
        init_pmm (mboot_ptr->mem_upper);
        printk(" + Initializing virtual memory manager\n");
        init_vmm ();
        
}

int kernel_main(multiboot_t *mboot_ptr)
{
        kernel_early(mboot_ptr);
        kernel_elf = elf_from_multiboot(mboot_ptr);
        
        //printk("Hello, kernel World!\n");
        asm volatile("int $0x3");
        asm volatile("int $0x4");
        //asm volatile("sti");
        //panic ("Testing panic mechanism");
        return (0xdeadbeef);
}
