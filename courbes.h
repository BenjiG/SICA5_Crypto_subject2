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

typedef struct {
	mpz_t _a1;
	mpz_t _a2;
	mpz_t _a3;
	mpz_t _a4;
	mpz_t _a6;
} equation_t;

typedef equation_t* ptr_equation_t;

void equation_init_set(ptr_equation_t E, const char* value_a1, const char* value_a2, const char* value_a3, const char* value_a4, const char* value_a6, int base);

// le point Q est l'oppose du point P par rapport a l'equation de la CE E
void oppose_point (ptr_equation_t E, ptr_point_t P, ptr_point_t Q);

//le point R est le resultat de l'addition du point P et Q par rapport a l'equation de la CE E
void addition_point_distinct (ptr_equation_t E, ptr_point_t P, ptr_point_t Q, ptr_point_t R);

//le point R est le resultat de l'addition du point P et Q par rapport a l'equation de la CE E
void addition_point (ptr_equation_t E, ptr_point_t P, ptr_point_t Q, ptr_point_t R);

//le point D est le resultat du doublement du point P par rapport a l'equation de la CE E
void doublement_point (ptr_equation_t E, ptr_point_t P, ptr_point_t D);

//le point R est le resultat de n fois le point P par rapport a l'equation de la CE E
void multiple_point (ptr_equation_t E, ptr_point_t P, int n, ptr_point_t R);


#endif /* COURBES_H_ */
