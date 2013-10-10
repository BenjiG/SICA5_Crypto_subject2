/*
 * main.c
 *
 *  Created on: 7 oct. 2013
 *      Author: sanchez
 */


#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include "point.h"
#include "courbes.h"

int main(void)
{
//	point_t P;
//	point_init(&P);
//
//	point_t Q;
//	point_init(&Q);
//
//	point_t Result;
//	point_init(&Result);
//
//
//
	int i;
//	for (i = 0; i < 163; ++i)
//	{
//		P._x[i] = rand() % 2;
//		Q._x[i] = rand() % 2;
//	}
//
//	bases_add(P._x,Q._x,Result._x);
//	point_print(&P, "P");
//	point_print(&Q, "Q");
//	point_print(&Result, "R");
	int *f;
	f = malloc(sizeof(int) * (4*7+1));
	F(4,7,17,f);
	for(i = 1; i < 4*7+1; ++i)
		printf("F(%d) = %d \n",i,f[i]);
	bases_t a = {1,0,1,0,1,1,1};
	bases_t b = {1,1,0,0,0,0,1};
	bases_t c;
	bases_mul(4,7,a,b,c,f);
	for(i = 0; i < 7; ++i)
	{
		printf("c(%d) = %d \n",i,c[i]);
	}
	free(f);
	return EXIT_SUCCESS;
}
