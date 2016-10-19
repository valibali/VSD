/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   gdt.h
 * Author: Balazs Valkony
 *
 * Created on 2016. október 16., 20:17
 */

#ifndef GDT_H
#define GDT_H

typedef struct {
	/* Limits */
	uint16_t limit_low;
	/* Segment address */
	uint16_t base_low;
	uint8_t base_middle;
	/* Access modes */
	uint8_t access;
	uint8_t granularity;
	uint8_t base_high;
} __attribute__((packed)) gdt_entry_t;

typedef struct {
	uint16_t limit;
	uintptr_t base;
} __attribute__((packed)) gdt_pointer_t;

extern void gdt_install(void);




#endif /* GDT_H */

