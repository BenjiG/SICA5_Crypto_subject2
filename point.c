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
	mpz_init(P->_x);
	mpz_init(P->_y);

}//point_init()

void point_clear (ptr_point_t P)
{
	mpz_clear(P->_x);
	mpz_clear(P->_y);

}//point_clear()

void point_print (ptr_point_t P, char * name)
{
	gmp_printf("%s (%Zd; %Zd) \n",name,P->_x, P->_y);

}//point_print()


void point_set_x (ptr_point_t P, const char * value_x, int base)
{
	mpz_set_str(P->_x,value_x,base);

}//point_set_x()

void point_set_y (ptr_point_t P, const char * value_y, int base)
{
	mpz_set_str(P->_y,value_y,base);

}//point_set_y()

void point_set_xy (ptr_point_t P, const char * value_x, const char * value_y, int base)
{
	point_set_x(P,value_x,base);
	point_set_y(P,value_y,base);

}//point_set_xy()
