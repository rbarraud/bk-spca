/*
 * Copyright Divakar Viswanath, 2009-2014
 */

/*     
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of version 2 of the GNU General Public License as 
 * published by the Free Software Foundation.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include "volatile.hh"

void addx(int *restrict ptr, int *restrict list, int n){
	for(int i=0; i < n; i++)
		list[i] += *ptr;
}

void vaddx(volatile int *restrict ptr, int *restrict list, int n){
	for(int i=0; i < n; i++)
		list[i] += *ptr;
}
