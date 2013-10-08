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

	equation_t E;
	point_t Q;
	point_init(&Q);
	equation_init_set(&E,"0","0","0","1","1",16);


	oppose_point(&E,&P,&Q);

	point_print(&P, "P");
	point_print(&Q, "Q");
	return EXIT_SUCCESS;
}
