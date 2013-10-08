/*
 * courbes.c
 *
 *  Created on: 8 oct. 2013
 *      Author: sanchez
 */

#include <gmp.h>

#include "point.h"
#include "courbes.h"

void equation_init_set(ptr_equation_t E, const char* value_a1, const char* value_a2, const char* value_a3, const char* value_a4, const char* value_a6, int base)
{
	mpz_init_set_str(E->_a1,value_a1,base);
	mpz_init_set_str(E->_a2,value_a2,base);
	mpz_init_set_str(E->_a3,value_a3,base);
	mpz_init_set_str(E->_a4,value_a4,base);
	mpz_init_set_str(E->_a6,value_a6,base);
}

void oppose_point (ptr_equation_t E, ptr_point_t P, ptr_point_t Q)
{
	//init du point Q
	point_init(Q);

	//X
	mpz_set(Q->_x,P->_x);

	//Y
	mpz_t zero;
	mpz_t r1;
	mpz_init_set_ui(zero,0);
	mpz_init_set_ui(r1,0);

	//Y_q = -Y_p
	mpz_sub(Q->_y,zero,P->_y);

	//r1 = a1 * X_p
	mpz_mul(r1,E->_a1,P->_x);

	//Y_q = Y_q - r1
	mpz_sub(Q->_y,Q->_y,r1);

	//Y_q = Y_q - a2
	mpz_sub(Q->_y,Q->_y,E->_a2);


}//oppose_point()



