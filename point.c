/*
 * point.c
 *
 *  Created on: 7 oct. 2013
 *      Author: sanchez
 */

#include <gmp.h>

#include "point.h"


void point_init (ptr_point_t P)
{
	int i;
	for(i = 0; i < 163; ++i){
		P->_x[i] = 0;
		P->_y[i] = 0;
	}

}//point_init()

void point_print (ptr_point_t P, char * name)
{

	int i;
	printf("%s ( X = [",name);
	for(i = 0; i < 162; ++i)
	{
		printf("%d,",P->_x[i]);
	}
	printf("%d];",P->_x[162]);
	printf(" Y = [");
	for(i = 0; i < 162; ++i)
	{
		printf("%d,",P->_y[i]);
	}
	printf("%d])\n",P->_y[162]);
}//point_print()


void bases_add (bases_t a, bases_t b, bases_t c)
{
	int i;
	for(i = 0; i < 163; ++i)
	{
		c[i]=(a[i] + b[i]) % 2;
	}
}//bases_add()


void F (int T, int m, int u, int *f)
{
	int p = T * m + 1;
	int n, i, w, j;
//	for(i = 0; i < p; ++i)
//		f [i] = 1;
	w = 1;
	j = 0;
	for(j = 0; j < T; ++j)
	{
		n = w;
		i = 0;
		for(i = 0; i < m; ++i)
		{
			f[n] = i;
			n = (2 * n) % p;
		}
		w = (u * w) % p;
	}
}

int F_uv (int T, int m, bases_t u, bases_t v, int* f)
{
	int p = T * m + 1;
	int k = 1;
	int result = 0;
	for(k = 1; k < p - 1; ++k)
	{
		result += u[f[k+1]] * v[f[p-k]];
	}
	return result % 2;
}

void bases_mul (int T, int m, bases_t a, bases_t b, bases_t c, int *f)
{
	//
	bases_t u, v;
	int i, k;
	for(i = 0; i < m; ++i)
	{
		u[i] = a[i];
		v[i] = b[i];
	}

	for (k = 0; k < m; ++k)
	{
		c[k] = F_uv(T,m,u,v,f);
		left_shift(u);
		left_shift(v);
	}
}//bases_mul()


void left_shift(int * tab)
{
	int memo = tab[0];
	int i = 0;
	for(i = 0; i < (M-1); ++i)
	{
		tab[i]=tab[i+1];
	}
	tab[M-1] = memo;
}
