/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   gdt.c
 * Author: Balazs Valkony
 *
 * Created on 2016. október 16., 20:27
 */

#include "kernel/common.h"
#include "kernel/gdt.h"

static struct {
    gdt_entry_t entries[6];
    gdt_pointer_t pointer;
    //tss_entry_t tss;
} gdt __attribute__((used));

#define ENTRY(X) (gdt.entries[(X)])

static void gdt_set_gate(uint8_t num, uint64_t base, uint64_t limit, uint8_t access, uint8_t gran);
extern void gdt_flush(uintptr_t);

void gdt_install(void) {
	gdt_pointer_t *gdtp = &gdt.pointer;
	gdtp->limit = sizeof gdt.entries - 1;
	gdtp->base = (uintptr_t)&ENTRY(0);

	gdt_set_gate(0, 0, 0, 0, 0);                /* NULL segment */
	gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); /* Code segment */
	gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); /* Data segment */
	gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); /* User code */
	gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); /* User data */

	//write_tss(5, 0x10, 0x0);

	/* Go go go */
	gdt_flush((uintptr_t)gdtp);
	//tss_flush();
}

void gdt_set_gate(uint8_t num, uint64_t base, uint64_t limit, uint8_t access, uint8_t gran) {
	/* Base Address */
	ENTRY(num).base_low = (base & 0xFFFF);
	ENTRY(num).base_middle = (base >> 16) & 0xFF;
	ENTRY(num).base_high = (base >> 24) & 0xFF;
	/* Limits */
	ENTRY(num).limit_low = (limit & 0xFFFF);
	ENTRY(num).granularity = (limit >> 16) & 0X0F;
	/* Granularity */
	ENTRY(num).granularity |= (gran & 0xF0);
	/* Access flags */
	ENTRY(num).access = access;
}

