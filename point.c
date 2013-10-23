/*
 * point.c
 *
 *  Created on: 7 oct. 2013
 *      Author: sanchez
 */

#include <gmp.h>

#include "point.h"
#include <stdlib.h>
#include <stdio.h>

void point_init (ptr_point_t Point)
{
	bases_init(Point->_x);
	bases_init(Point->_y);
	Point->_inf = 0;
}//point_init()

void point_print (ptr_point_t Point, char * name)
{
	printf("%s ( X = [",name);
	bases_print(Point->_x);
	printf("%d];",Point->_x[162]);
	printf(" Y = [");
	bases_print(Point->_y);
	printf("%d])\n",Point->_y[162]);
}//point_print()

int point_equal (ptr_point_t PointA, ptr_point_t PointB)
{
	return (bases_equal(PointA->_x,PointB->_x) && bases_equal(PointA->_y,PointB->_y) && (PointA->_inf == PointB->_inf));
}//point_equal()

//PointA = PointB
void point_set_point (ptr_point_t PointA, ptr_point_t PointB)
{
	bases_set_bases(PointA->_x, PointB->_x);
	bases_set_bases(PointA->_y,PointB->_y);
	PointA->_inf = PointB->_inf;
}//point_set_point()
