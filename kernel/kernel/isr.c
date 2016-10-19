/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   isr.c
 * Author: Balazs Valkony
 *
 * Created on 2016. október 16., 21:03
 */
#include "kernel/common.h"
#include "kernel/idt.h"
#include "kernel/tty.h"
#include "stdio.h"

#define ISR_COUNT 32

static struct {
	size_t index;
	void (*stub)(void);
} isrs[32 + 1] __attribute__((used));

static irq_handler_t isr_routines[256] = { 0 };

void isrs_install_handler(size_t isrs, irq_handler_t handler) {
	isr_routines[isrs] = handler;
}

void isrs_uninstall_handler(size_t isrs) {
	isr_routines[isrs] = 0;
}

void isrs_install(void) {
	idt_set_gate ( 0, (idt_gate_t)isr0 , 0x08, 0x8E);
        idt_set_gate ( 1, (idt_gate_t)isr1 , 0x08, 0x8E);
        idt_set_gate ( 2, (idt_gate_t)isr2 , 0x08, 0x8E);
        idt_set_gate ( 3, (idt_gate_t)isr3 , 0x08, 0x8E);
        idt_set_gate ( 4, (idt_gate_t)isr4 , 0x08, 0x8E);
        idt_set_gate ( 5, (idt_gate_t)isr5 , 0x08, 0x8E);
        idt_set_gate ( 6, (idt_gate_t)isr6 , 0x08, 0x8E);
        idt_set_gate ( 7, (idt_gate_t)isr7 , 0x08, 0x8E);
        idt_set_gate ( 8, (idt_gate_t)isr8 , 0x08, 0x8E);
        idt_set_gate ( 9, (idt_gate_t)isr9 , 0x08, 0x8E);
        idt_set_gate (10, (idt_gate_t)isr10, 0x08, 0x8E);
        idt_set_gate (11, (idt_gate_t)isr11, 0x08, 0x8E);
        idt_set_gate (12, (idt_gate_t)isr12, 0x08, 0x8E);
        idt_set_gate (13, (idt_gate_t)isr13, 0x08, 0x8E);
        idt_set_gate (14, (idt_gate_t)isr14, 0x08, 0x8E);
        idt_set_gate (15, (idt_gate_t)isr15, 0x08, 0x8E);
        idt_set_gate (16, (idt_gate_t)isr16, 0x08, 0x8E);
        idt_set_gate (17, (idt_gate_t)isr17, 0x08, 0x8E);
        idt_set_gate (18, (idt_gate_t)isr18, 0x08, 0x8E);
        idt_set_gate (19, (idt_gate_t)isr19, 0x08, 0x8E);
        idt_set_gate (20, (idt_gate_t)isr20, 0x08, 0x8E);
        idt_set_gate (21, (idt_gate_t)isr21, 0x08, 0x8E);
        idt_set_gate (22, (idt_gate_t)isr22, 0x08, 0x8E);
        idt_set_gate (23, (idt_gate_t)isr23, 0x08, 0x8E);
        idt_set_gate (24, (idt_gate_t)isr24, 0x08, 0x8E);
        idt_set_gate (25, (idt_gate_t)isr25, 0x08, 0x8E);
        idt_set_gate (26, (idt_gate_t)isr26, 0x08, 0x8E);
        idt_set_gate (27, (idt_gate_t)isr27, 0x08, 0x8E);
        idt_set_gate (28, (idt_gate_t)isr28, 0x08, 0x8E);
        idt_set_gate (29, (idt_gate_t)isr29, 0x08, 0x8E);
        idt_set_gate (30, (idt_gate_t)isr30, 0x08, 0x8E);
        idt_set_gate (31, (idt_gate_t)isr31, 0x08, 0x8E);        
}

void idt_handler(registers_t * r) {
	irq_handler_t handler = isr_routines[r->int_no];
	if (handler) {
		handler(r);
	} 
        else {
		terminal_writestring("Unhandled interrupt: ");
                terminal_write_dec((uint32_t)(r->int_no));
                terminal_writestring("\n");
	}
}

