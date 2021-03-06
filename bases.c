/*
 * bases.c
 *
 *  Created on: 10 oct. 2013
 *      Author: sanchez
 */

#include <gmp.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bases.h"

void bases_init(bases_t a)
{
	int i;
	for(i = 0; i < M; ++i)
		a[i] = 0;
}//bases_init()

int bases_equal(bases_t a, bases_t b)
{
	int i;
	for(i = 0; i < M; ++i)
		if(a[i] != b[i])return 0;
	return 1;
}//bases_equal()

void bases_add (bases_t a, bases_t b, bases_t c)
{
	int i;
	for(i = 0; i < 163; ++i)
	{
		c[i]=(a[i] + b[i]) % 2;
	}
}//bases_add()


void bases_mul_F (int *f)
{
	int p = T * M + 1;
	int n, i, w, j;
	w = 1;
	j = 0;
	for(j = 0; j < T; ++j)
	{
		n = w;
		i = 0;
		for(i = 0; i < M; ++i)
		{
			f[n] = i;
			n = (2 * n) % p;
		}
		w = (U * w) % p;
	}
}//bases_mul_F()

int bases_mul_F_uv (bases_t u, bases_t v)
{
	int p = T * M + 1;
	int k = 1;
	int result = 0;
	for(k = 1; k < p - 1; ++k)
	{
		result += u[f[k+1]] * v[f[p-k]];
	}
	return result % 2;
}//bases_mul_F_uv()

void bases_mul (bases_t a, bases_t b, bases_t c)
{
	//
	bases_t u, v;
	int i, k;
	for(i = 0; i < M; ++i)
	{
		u[i] = a[i];
		v[i] = b[i];
	}

	for (k = 0; k < M; ++k)
	{
		c[k] = bases_mul_F_uv(u,v);
		bases_mul_left_shift(u);
		bases_mul_left_shift(v);
	}
}//bases_mul()


void bases_mul_left_shift(int * tab)
{
	int memo = tab[0];
	int i = 0;
	for(i = 0; i < (M-1); ++i)
	{
		tab[i]=tab[i+1];
	}
	tab[M-1] = memo;
}//bases_mul_left_shift()

void bases_mul_rg_shift(int * tab)
{
	int memo = tab[M-1];
	int i = 0;
	for(i = M-2; i > 1; --i)
	{
		tab[i]=tab[i-1];
	}
	tab[0] = memo;
}//bases_mul_left_shift()

void bases_print(bases_t a)
{
	int i = 0;
	for(i = 0; i < M; ++i)
	{
		printf("%d",a[i]);
		//if(i == M-1)printf(" \t%d",i);
	}
}//bases_print()

void bases_to_string(bases_t a, char *str)
{
	int i = 0;
	for(i = 0; i < M; ++i)
	{
		sprintf(str, "%s%d",str, a[i]);
	}
}//bases_to_string()

void string_to_int (char *string, mpz_t integer)
{
	mpz_init_set_str(integer,string,2);
}//bases_to_int()

void int_to_string (mpz_t integer, char *string)
{
	mpz_get_str(string,2,integer);
}//int_to_bases()

void string_to_bases(bases_t a, char *str)
{
	int i = 0;
	for(i = 0; i < strlen(str); ++i)
		a[i] = str[i] - '0';
	for(i = strlen(str); i < M; ++i)
		a[i] = 0;
}//string_to_bases()

void bases_to_int(bases_t bases, mpz_t integer)
{
	char str [M];
	bases_to_string(bases,str);
	string_to_int(str,integer);
}//bases_to_int()

void int_to_bases(mpz_t integer, bases_t bases)
{
	char str [M];
	int_to_string(integer,str);
	string_to_bases(bases,str);
}//int_to_bases()

void bases_inverse(bases_t bases, bases_t bases_inv)
{
	bases_t z, y;
	int k = 0;
	bases_init(z);bases_init(y);
	bases_set_bases(y,bases);
	for(k = 0; k < M-2; ++k)
	{
		//bases_mul(y,y,z);
		bases_set_bases(z,y);
		bases_mul_left_shift(z);
		bases_mul(z,bases,y);
	}
	//bases_mul(y,y,bases_inv);
	bases_mul_left_shift(y);
	bases_set_bases(bases_inv,y);
}//bases_inverse()


//bases_a = bases_b
void bases_set_bases(bases_t bases_a, bases_t bases_b)
{
	int i;
	for(i = 0; i < M; ++i)
		bases_a[i] = bases_b[i];
}//bases_set_bases()
