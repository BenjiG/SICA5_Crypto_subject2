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

int main(void)
{
	point_t P;
	point_init(&P);
	point_set_x(&P,"10",10);
	point_set_y(&P,"5",10);
	point_print(&P,"P");
	point_set_xy(&P,"5","10",10);
	point_print(&P,"P");
	point_clear(&P);
	return EXIT_SUCCESS;
}
