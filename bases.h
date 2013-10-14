/*
 * bases.h
 *
 *  Created on: 10 oct. 2013
 *      Author: sanchez
 */

#ifndef BASES_H_
#define BASES_H_

#include <gmp.h>

#define M 163

#define T 4

#define U 17


typedef int  bases_t [M];



void bases_add (bases_t a, bases_t b, bases_t c);

void bases_mul (bases_t a, bases_t b, bases_t c, int *f);

void bases_mul_F (int* f);

int bases_mul_F_uv (bases_t u, bases_t v, int* f);

void bases_mul_left_shift(int * tab);

void bases_to_int (char * a, mpz_t val);

void bases_to_string(bases_t a, char * str);

#endif /* BASES_H_ */
