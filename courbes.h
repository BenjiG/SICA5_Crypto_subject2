/*
 * courbes.h
 *
 *  Created on: 8 oct. 2013
 *      Author: sanchez
 */

#ifndef COURBES_H_
#define COURBES_H_

#include "point.h"

typedef struct {
	int _a1;
	int _a2;
	int _a3;
	int _a4;
	int _a6;
} equation_t;

typedef equation_t* ptr_equation_t;

// le point Q est l'oppose du point P par rapport a l'equation de la CE E
void oppose_point (ptr_equation_t E, ptr_point_t P, ptr_point_t Q);

//le point R est le resultat de l'addition du point P et Q par rapport a l'equation de la CE E
void addition_point (ptr_equation_t E, ptr_point_t P, ptr_point_t Q, ptr_point_t R);

//le point D est le resultat du doublement du point P par rapport a l'equation de la CE E
void doublement_point (ptr_equation_t E, ptr_point_t P, ptr_point_t D);

//le point R est le resultat de n fois le point P par rapport a l'equation de la CE E
void multiple_point (ptr_equation_t E, ptr_point_t P, int n, ptr_point_t R);


#endif /* COURBES_H_ */
