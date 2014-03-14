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

#ifndef __DVRANDOM__
#define __DVRANDOM__
#include <mkl.h>

class Random{
 private:
  VSLStreamStatePtr stream;
  Random(const Random& );
 public:
  Random(unsigned int seed = 0){
    int status = vslNewStream(&stream, VSL_BRNG_MCG59, seed);
  }
  /* returns normally distributed random variable of variance sigma */
  double randn(double sigma = 1.0){
    double val;
    int status = vdRngGaussian(VSL_METHOD_DGAUSSIAN_ICDF,
			       stream, 1, &val, 0, sigma);//mean=0
    return val;
  }
  /* returns variable uniformly distributed in [a,b] */
  double rand(double a = 0.0, double b = 1.0){
    double val;
    int status = vdRngUniform(VSL_METHOD_DUNIFORM_STD_ACCURATE,
			      stream, 1, &val, a, b);
    return val;
  }
  ~Random(){
    int status = vslDeleteStream(&stream);
  }
};
#endif

