/*
 * point.c
 *
 *  Created on: 7 oct. 2013
 *      Author: sanchez
 */

#include <gmp.h>

#include "point.h"


void point_init (ptr_point_t Point)
{
	int i;
	for(i = 0; i < 163; ++i){
		Point->_x[i] = 0;
		Point->_y[i] = 0;
	}

}//point_init()

void point_print (ptr_point_t Point, char * name)
{

	int i;
	printf("%s ( X = [",name);
	for(i = 0; i < 162; ++i)
	{
		printf("%d",Point->_x[i]);
	}
	printf("%d];",Point->_x[162]);
	printf(" Y = [");
	for(i = 0; i < 162; ++i)
	{
		printf("%d,",Point->_y[i]);
	}
	printf("%d])\n",Point->_y[162]);
}//point_print()

