/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   pmm.h
 * Author: Balazs Valkony
 *
 * Created on 2016. október 25., 20:25
 */

#ifndef PMM_H
#define PMM_H

#define PMM_STACK_ADDR 0xFF000000

void init_pmm (uint32_t start);

uint32_t pmm_alloc_page ();

void pmm_free_page (uint32_t p);

#endif /* PMM_H */

