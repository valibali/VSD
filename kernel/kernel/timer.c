/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   timer.c
 * Author: Balazs Valkony
 *
 * Created on 2016. október 18., 11:50
 */

#include "kernel/common.h"
#include "kernel/idt.h"
#include "kernel/tty.h"

uint32_t tick = 0;

int timer_callback (registers_t *regs)
{
    terminal_writestring("Tick: ");
    terminal_write_dec((uint32_t)(++tick));
    terminal_writestring("\n");
    return 0;
}

void init_timer (uint32_t frequency)
{
  // Firstly, register our timer callback.
  irq_install_handler(IRQ0, &timer_callback);

  // The value we send to the PIT is the value to divide it's input clock
  // (1193180 Hz) by, to get our required frequency. Important to note is
  // that the divisor must be small enough to fit into 16-bits.
  uint32_t divisor = 1193180 / frequency;

  // Send the command byte.
  outb(0x43, 0x36);

  // Divisor has to be sent byte-wise, so split here into upper/lower bytes.
  uint8_t l = (uint8_t)(divisor & 0xFF);
  uint8_t h = (uint8_t)( (divisor>>8) & 0xFF );

  // Send the frequency divisor.
  outb(0x40, l);
  outb(0x40, h);
}
