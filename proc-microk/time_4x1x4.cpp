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

#include "../utils/TimeStamp.hh"
#include <iostream>

extern void multxmm4x1x4(double *a, double *b, double *c);
extern void multxmm4x1x4R(double *a, double *b, double *c);



int main(){
	__declspec(align(16)) double a[4] = {0};
	__declspec(align(16)) double b[4] = {0};
	__declspec(align(16)) double c[16] = {0};
	
	for(int i=0; i < 4; i++){
		a[i]=1.0/(i+7);
		b[i]=i+1;
	}
	for(int i=0; i < 16; i++)
		c[i] = 0;

	TimeStamp clk;
	double cycles;
	clk.tic();
	
	for(int i=0; i < 1000*1000*1000; i++)
		multxmm4x1x4(a, b, c);
	
	cycles = clk.toc();
	std::cout<<std::endl
	    <<"number of cycles per 4x1x4 iteration = "
		 <<cycles/1000/1000/1000<<std::endl;
	
	clk.tic();
	multxmm4x1x4R(a, b, c);
	cycles = clk.toc();
	std::cout<<std::endl
	    <<"number of cycles per 4x1x4 iteration (c out of loop) = "
		 <<cycles/1000/1000/1000<<std::endl;

}
