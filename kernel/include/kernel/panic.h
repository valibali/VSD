/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   panic.h
 * Author: Balazs Valkony
 *
 * Created on 2016. október 18., 14:41
 */

#ifndef PANIC_H
#define PANIC_H


void panic (const char *msg);
void print_stack_trace(void);

#endif /* PANIC_H */

