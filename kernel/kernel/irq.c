/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   irq.c
 * Author: Balazs Valkony
 *
 * Created on 2016. október 18., 10:59
 */

#include "kernel/common.h"
#include "kernel/idt.h"

/* Programmable interrupt controller */
#define PIC1           0x20
#define PIC1_COMMAND   PIC1
#define PIC1_OFFSET    0x20
#define PIC1_DATA      (PIC1+1)

#define PIC2           0xA0
#define PIC2_COMMAND   PIC2
#define PIC2_OFFSET    0x28
#define PIC2_DATA      (PIC2+1)

#define PIC_EOI        0x20

#define ICW1_ICW4      0x01
#define ICW1_INIT      0x10

#define PIC_WAIT() \
	do { \
		/* May be fragile */ \
		asm volatile("jmp 1f\n\t" \
		             "1:\n\t" \
		             "    jmp 2f\n\t" \
		             "2:"); \
	} while (0)

/* Interrupts */
static volatile int sync_depth = 0;

#define SYNC_CLI() asm volatile("cli")
#define SYNC_STI() asm volatile("sti")

void int_disable(void) {
	/* Check if interrupts are enabled */
	uint32_t flags;
	asm volatile("pushf\n\t"
	             "pop %%eax\n\t"
	             "movl %%eax, %0\n\t"
	             : "=r"(flags)
	             :
	             : "%eax");

	/* Disable interrupts */
	SYNC_CLI();

	/* If interrupts were enabled, then this is the first call depth */
	if (flags & (1 << 9)) {
		sync_depth = 1;
	} else {
		/* Otherwise there is now an additional call depth */
		sync_depth++;
	}
}

void int_resume(void) {
	/* If there is one or no call depths, reenable interrupts */
	if (sync_depth == 0 || sync_depth == 1) {
		SYNC_STI();
	} else {
		sync_depth--;
	}
}

void int_enable(void) {
	sync_depth = 0;
	SYNC_STI();
}

/* Interrupt Requests */
#define IRQ_CHAIN_SIZE  16
#define IRQ_CHAIN_DEPTH 4

static void (*irqs[IRQ_CHAIN_SIZE])(void);
static irq_handler_chain_t irq_routines[IRQ_CHAIN_SIZE * IRQ_CHAIN_DEPTH] = { NULL };

void irq_install_handler(size_t irq, irq_handler_chain_t handler) {
	/* Disable interrupts when changing handlers */
	SYNC_CLI();
	for (size_t i = 0; i < IRQ_CHAIN_DEPTH; i++) {
		if (irq_routines[i * IRQ_CHAIN_SIZE + irq])
			continue;
		irq_routines[i * IRQ_CHAIN_SIZE + irq] = handler;
		break;
	}
	SYNC_STI();
}

void irq_uninstall_handler(size_t irq) {
	/* Disable interrupts when changing handlers */
	SYNC_CLI();
	for (size_t i = 0; i < IRQ_CHAIN_DEPTH; i++)
		irq_routines[i * IRQ_CHAIN_SIZE + irq] = NULL;
	SYNC_STI();
}

static void irq_remap(void) {
	/* Cascade initialization */
	outb(PIC1_COMMAND, ICW1_INIT|ICW1_ICW4); PIC_WAIT();
	outb(PIC2_COMMAND, ICW1_INIT|ICW1_ICW4); PIC_WAIT();

	/* Remap */
	outb(PIC1_DATA, PIC1_OFFSET); PIC_WAIT();
	outb(PIC2_DATA, PIC2_OFFSET); PIC_WAIT();

	/* Cascade identity with slave PIC at IRQ2 */
	outb(PIC1_DATA, 0x04); PIC_WAIT();
	outb(PIC2_DATA, 0x02); PIC_WAIT();

	/* Request 8086 mode on each PIC */
	outb(PIC1_DATA, 0x01); PIC_WAIT();
	outb(PIC2_DATA, 0x01); PIC_WAIT();
}

static void irq_setup_gates(void) {
    
/*Until simbol lookup is not working...
	for (size_t i = 0; i < IRQ_CHAIN_SIZE; i++) {
		idt_set_gate(32 + i, irqs[i], 0x08, 0x8E);
	}
*/
}

void irq_install(void) {
/* Until simbol lookup is not working...
	char buffer[16];
	for (int i = 0; i < IRQ_CHAIN_SIZE; i++) {
		sprintf(buffer, "_irq%d", i);
		irqs[i] = symbol_find(buffer);
	}
*/
	
  idt_set_gate (32, (idt_gate_t)irq0, 0x08, 0x8E);
  idt_set_gate (33, (idt_gate_t)irq1, 0x08, 0x8E);
  idt_set_gate (34, (idt_gate_t)irq2, 0x08, 0x8E);
  idt_set_gate (35, (idt_gate_t)irq3, 0x08, 0x8E);
  idt_set_gate (36, (idt_gate_t)irq4, 0x08, 0x8E);
  idt_set_gate (37, (idt_gate_t)irq5, 0x08, 0x8E);
  idt_set_gate (38, (idt_gate_t)irq6, 0x08, 0x8E);
  idt_set_gate (39, (idt_gate_t)irq7, 0x08, 0x8E);
  idt_set_gate (40, (idt_gate_t)irq8, 0x08, 0x8E);
  idt_set_gate (41, (idt_gate_t)irq9, 0x08, 0x8E);
  idt_set_gate (42, (idt_gate_t)irq10, 0x08, 0x8E);
  idt_set_gate (43, (idt_gate_t)irq11, 0x08, 0x8E);
  idt_set_gate (44, (idt_gate_t)irq12, 0x08, 0x8E);
  idt_set_gate (45, (idt_gate_t)irq13, 0x08, 0x8E);
  idt_set_gate (46, (idt_gate_t)irq14, 0x08, 0x8E);
  idt_set_gate (47, (idt_gate_t)irq15, 0x08, 0x8E);
  idt_set_gate (255, (idt_gate_t)isr255, 0x08, 0x8E);
  
    irq_remap();
    irq_setup_gates();
}

void irq_ack(size_t irq_no) {
	if (irq_no >= 8) {
		outb(PIC2_COMMAND, PIC_EOI);
	}
	outb(PIC1_COMMAND, PIC_EOI);
}
    
void irq_handler(registers_t *r) {
	/* Disable interrupts when handling */
	int_disable();

	if (r->int_no <= 47 && r->int_no >= 32) {
		for (size_t i = 0; i < IRQ_CHAIN_DEPTH; i++) {
			irq_handler_chain_t handler = irq_routines[i * IRQ_CHAIN_SIZE + (r->int_no - 32)];
			if (handler && handler(r)) {
				goto done;
			}
		}
		irq_ack(r->int_no - 32);
	}
done:        
	int_resume();
}
