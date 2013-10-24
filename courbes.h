/*
 * courbes.h
 *
 *  Created on: 8 oct. 2013
 *      Author: sanchez
 */

#ifndef COURBES_H_
#define COURBES_H_

#include <gmp.h>
#include "point.h"


typedef struct curve {
	bases_t _a1;
	bases_t _a2;
	bases_t _a3;
	bases_t _a4;
	bases_t _a6;
}curve_t, * ptr_curve_t;



void addition_point_CE (ptr_curve_t E, ptr_point_t A, ptr_point_t B, ptr_point_t C);

void addition_distinct_point_CE (ptr_curve_t E, ptr_point_t A, ptr_point_t B, ptr_point_t C);

void oppose_point_CE (ptr_curve_t E, ptr_point_t A, ptr_point_t C);

void double_point_CE (ptr_curve_t E, ptr_point_t A, ptr_point_t AA);

void multiple_point_CE (ptr_curve_t E, ptr_point_t A, bases_t k, ptr_point_t C);

void init_data_curve (ptr_point_t G, ptr_curve_t E);

void multiple_addition_point_CE(ptr_curve_t E, bases_t g_bases, ptr_point_t G, bases_t q_bases, ptr_point_t Q, ptr_point_t GQ, ptr_point_t R);

#endif /* COURBES_H_ */
