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
	point_t P;
	point_init(&P);

	point_t Q;
	point_init(&Q);

	point_t Result;
	point_init(&Result);

	curve_t E;
	bases_init(E._a1);bases_init(E._a2);bases_init(E._a3);bases_init(E._a4);bases_init(E._a6);

	int *f;
	int p = T * M + 1;
	f = malloc(sizeof(int) * (p));
	bases_mul_F(f);

	int i;
	for (i = 0; i < 163; ++i)
	{
		P._x[i] = rand() % 2;
		Q._x[i] = rand() % 2;
		P._y[i] = rand() % 2;
		Q._y[i] = rand() % 2;
	}

	point_print(&P, "P");
	point_print(&Q, "Q");
	addition_point_CE(f,&E,&P,&Q,&Result);
	point_print(&Result, "R");

	oppose_point_CE(f,&E,&P,&Result);
	point_print(&Result, "R");
	free(f);
	return EXIT_SUCCESS;
}
