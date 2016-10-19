/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   printk.c
 * Author: Balazs Valkony
 *
 * Created on 2016. október 18., 14:52
 */

#include "stdio.h"
#include "printk.h"
#include "vsprintf.h"
#include <stdarg.h>

void printk (const char *fmt, ...)
{
	static char buf [1024];

 	va_list args;
 	int i;
 
 	va_start(args, fmt);
 	i = vsprintf(buf,fmt,args);
 	va_end(args);

 	buf[i] = '\0';

 	printf (buf);
}
