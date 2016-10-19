/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   timer.h
 * Author: Balazs Valkony
 *
 * Created on 2016. október 11., 21:12
 */

#ifndef TIMER_H
#define TIMER_H

#include "kernel/common.h"

void init_timer (uint32_t frequency);
int timer_callback (registers_t *regs);

#endif
