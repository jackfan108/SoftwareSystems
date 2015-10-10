#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*

    Copyright 2007 Allen B. Downey

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    The GNU General Public License is available from
    http://www.gnu.org/licenses/.

*/

// generate a random float using the algorithm described
// at allendowney.com/research/rand
float my_random_float()
{
  int x, exp, mant;
  float f;

  // this union is for assembling the float.
  union {
    float f;
    int i;
  } b;

  // generate 31 random bits (assuming that RAND_MAX is 2^31 - 1
  x = random();

  // use bit-scan-forward to find the first set bit and
  // compute the exponent
  asm ("bsfl %1, %0"
       :"=r"(exp)
       :"r"(x)
      );
  exp = 126 - exp;

  // use the other 23 bits for the mantissa (for small numbers
  // this means we are re-using some bits)
  mant = x >> 8;
  b.i = (exp << 23) | mant;

  return b.f;
}

// alternative implementation of my algorithm that doesn't use
// embedded assembly
float my_random_float2()
{
  int x;
  int mant;
  int exp = 126;
  int mask = 1;

  union {
    float f;
    int i;
  } b;

  // generate random bits until we see the first set bit
  while (1) {
    x = random();
    if (x == 0) {
      exp -= 31;
    } else {
      break;
    }
  }

  // find the location of the first set bit and compute the exponent
  while (x & mask) {
    //printf("x&mask: %d\n", x & mask);
    //printf("mask: %d\n", mask);
    //printf("exp: %d\n", exp);
    mask <<= 1;
    exp--;
    //printf("x&mask: %d\n", x & mask);
    //printf("mask: %d\n", mask);
    //printf("exp: %d\n", exp);
  }

  // use the remaining bit as the mantissa
  //printf("x: %d\n", x);
  //printf("x rightshift 8 bits\n");
  mant = x >> 8;
  //printf("x: %d\n", x);
  //printf("sizeofx %zu\n", sizeof(x));
  //printf("mant: %d\n", mant);
  //printf("exp: %d\n", exp);
  //printf("exp << 23: %d\n", exp << 23);
  b.i = (exp << 23) | mant;
  //printf("b.i: %d\n", b.i);
  //printf("b.f: %f\n", b.f);

  return b.f;
}

// compute a random double using my algorithm
double my_random_double()
{
  long x;
  long mant;
  long exp = 1022; // 1023-1 exponent bias
  int mask = 1;

  union {
    double d;
    long l;
  } b;

  // generate random bits until we see the first set bit
  while (1) {
    x = random() << 32 | random();
    if (x == 0) {
      exp -= 31;
    } else {
      break;
    }
  }

  //printf("x:%li\n", x);

  // find the location of the first set bit and compute the exponent
  while (x & mask) {
    //printf("x&mask: %d\n", x & mask);
    //printf("mask: %d\n", mask);
    //printf("exp: %d\n", exp);
    mask <<= 1;
    exp--;
    //printf("x&mask: %d\n", x & mask);
    //printf("mask: %d\n", mask);
    //printf("exp: %li\n", exp);
  }

  // use the remaining bit as the mantissa
  //printf("x: %d\n", x);
  //printf("x rightshift 8 bits\n");
  mant = x >> 11; // 11 bits for the exponent
  //printf("x: %li\n", x);
  //printf("mant: %li\n", mant);
  //printf("exp: %d\n", exp);
  //printf("exp << 23: %d\n", exp << 23);
  b.l = (exp << 52) | mant; // 52 bits for the mantissa
  //printf("b.i: %d\n", b.i);
  //printf("b.f: %f\n", b.f);
  //printf("b.d: %f\n", b.d);
  return b.d;
}

// return a constant (this is a dummy function for time trials)
float dummy()
{
  float f = 0.5;

  return f;
}

// generate a random integer and convert to float (dummy function)
float dummy2()
{
  int x;
  float f;

  x = random();
  f = (float) x;

  return f;
}

// generate a random float using the standard algorithm
float random_float()
{
  int x;
  float f;

  x = random();
  f = (float) x / (float)RAND_MAX;

  return f;
}


// generate a random double using the standard algorithm
float random_double()
{
  int x;
  double f;

  x = random();
  f = (double) x / (double)RAND_MAX;

  return f;
}


