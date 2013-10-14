/*
 * bases.c
 *
 *  Created on: 10 oct. 2013
 *      Author: sanchez
 */

#include "bases.h"
#include <gmp.h>
#include <stdio.h>

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

int bases_mul_F_uv (bases_t u, bases_t v, int* f)
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

void bases_mul (bases_t a, bases_t b, bases_t c, int *f)
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
		c[k] = bases_mul_F_uv(u,v,f);
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

void bases_print(bases_t a)
{
	int i = 0;
	for(i = 0; i < M; ++i)
	{
		printf("%d",a[i]);
	}
}//bases_print()

void bases_to_string(bases_t a, char * str)
{
	int i = 0;
	*str = NULL;
	for(i = 0; i < M; ++i)
	{
		sprintf(str, "%s%d",str, a[i]);

	}
}//bases_print()

void bases_to_int (char *var, mpz_t val)
{
	mpz_init_set_str(val,var,2);
}
