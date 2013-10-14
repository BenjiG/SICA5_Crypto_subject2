/*
 * courbes.c
 *
 *  Created on: 8 oct. 2013
 *      Author: sanchez
 */

#include <gmp.h>

#include "point.h"
#include "courbes.h"


void addition_point_CE (ptr_curve_t E, ptr_point_t A, ptr_point_t B, ptr_point_t C)
{

}


void oppose_point_CE (ptr_curve_t E, ptr_point_t A, ptr_point_t C)
{
	bases_add(A->_x,C->_x,C->_x);
	bases_add(A->_x,A->_y,C->_y);
}
