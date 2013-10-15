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


void bases_init(bases_t a);

int bases_equal(bases_t a, bases_t b);

void bases_add (bases_t a, bases_t b, bases_t c);

void bases_mul (bases_t a, bases_t b, bases_t c, int *f);

void bases_mul_F (int* f);

int bases_mul_F_uv (bases_t u, bases_t v, int* f);

void bases_mul_left_shift(int * tab);

void bases_print(bases_t a);

void bases_to_int(bases_t bases, mpz_t integer);

void int_to_bases(mpz_t integer, bases_t bases);

void string_to_int (char *str, mpz_t integer);

void int_to_string (mpz_t integer, char *str);

void bases_to_string(bases_t bases, char *str);

void string_to_bases(bases_t bases, char *str);

void bases_inverse(bases_t bases, bases_t bases_inv);

void bases_set_bases(bases_t bases_a, bases_t bases_b);

#endif /* BASES_H_ */
