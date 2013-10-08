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
		c[i]=a[i] + b[i] % 2;
	}
}//bases_add()


