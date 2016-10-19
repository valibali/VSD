/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   isr.h
 * Author: Balazs Valkony
 *
 * Created on 2016. október 16., 22:23
 */

#ifndef ISR_H
#define ISR_H


void isrs_install(void);
void idt_handler(struct registers * r);

#endif /* ISR_H */

