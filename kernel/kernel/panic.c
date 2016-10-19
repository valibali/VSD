/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   panic.c
 * Author: Balazs Valkony
 *
 * Created on 2016. október 18., 14:36
 */

#include "kernel/common.h"
#include "kernel/multiboot.h"
#include "kernel/elf.h"
#include "kernel/panic.h"
#include "printk.h"



extern elf_t kernel_elf;

void panic (const char *msg)
{
  printk ("*** System panic: %s\n", msg);

  print_stack_trace ();
  printk ("***\n");
  for (;;) ;
}

void print_stack_trace()
{
    uint32_t *ebp, *eip;

    asm volatile ("mov %%ebp, %0" : "=r" (ebp));
    while (ebp) {
        eip = ebp + 1;
        printk("   [0x%x] %s\n", *eip, elf_lookup_symbol(*eip, &kernel_elf));
        ebp = (uint32_t*)*ebp;
    }
}

