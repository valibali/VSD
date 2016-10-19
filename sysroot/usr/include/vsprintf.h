/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   vsprintf.h
 * Author: Balazs Valkony
 *
 * Created on 2016. október 18., 14:55
 */

#ifndef VSPRINTF_H
#define VSPRINTF_H



#include <stdarg.h>

int vsprintf(char *buf, const char *fmt, va_list args);

#endif /* VSPRINTF_H */

