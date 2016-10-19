/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   idt.c
 * Author: Balazs Valkony
 *
 * Created on 2016. október 16., 20:48
 */

#include "kernel/common.h"
#include "string.h"
#include "kernel/idt.h"


static struct {
	idt_entry_t entries[256];
	idt_pointer_t pointer;
} idt __attribute__((used));

#define ENTRY(X) (idt.entries[(X)])
extern void idt_flush(uintptr_t);

void idt_set_gate(uint8_t num, idt_gate_t base, uint16_t sel, uint8_t flags) {
	ENTRY(num).base_low = ((uintptr_t)base & 0xFFFF);
	ENTRY(num).base_high = ((uintptr_t)base >> 16) & 0xFFFF;
	ENTRY(num).sel = sel;
	ENTRY(num).zero = 0;
	ENTRY(num).flags = flags | 0x60;
}

void idt_install(void) {
	idt_pointer_t * idtp = &idt.pointer;
	idtp->limit = sizeof idt.entries - 1;
	idtp->base = (uintptr_t)&ENTRY(0);
	memset(&ENTRY(0), 0, sizeof idt.entries);

	idt_flush((uintptr_t)idtp);
}

