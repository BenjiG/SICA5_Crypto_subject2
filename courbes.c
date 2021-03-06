/*
 * courbes.c
 *
 *  Created on: 8 oct. 2013
 *      Author: sanchez
 */

#include <gmp.h>

#include "point.h"
#include "courbes.h"

void addition_distinct_point_CE (ptr_curve_t E, ptr_point_t A, ptr_point_t B, ptr_point_t C)
{
	bases_t X, Y, X_inv, lambda;
	bases_t r0, r1, r2;
	bases_t val1;
	//X <- x_a + x_b
	bases_add(A->_x,B->_x,X);

	//lambda <- (y_a + y_b) / X ==> lambda <- (y_a + y_b) * X^-1
	bases_add(A->_y,B->_y,Y);
	bases_inverse(X,X_inv);
	bases_mul(Y,X_inv,lambda);


	//x_c <- lambda^2 + lambda + X + E->_a2
	bases_mul(lambda,lambda,r0);
	bases_add(r0,lambda,r1);
	bases_add(r1,X,r0);
	bases_add(r1,E->_a2,C->_x);

	//y_c <- (lambda+ 1)x_c + lambda x_a + y_a
	mpz_t v;
	mpz_init_set_ui(v,1);
	int_to_bases(v,val1);
	bases_add(lambda,val1,r0);
	bases_mul(r0,C->_x,r1);
	bases_mul(lambda,A->_x,r2);
	bases_add(r1,r2,r0);
	bases_add(r0,A->_y,C->_y);

}//addition_distinct_point_CE()

void addition_point_CE (ptr_curve_t E, ptr_point_t A, ptr_point_t B, ptr_point_t C)
{
	point_t O;
	point_t B_opp;

	point_init(&O);
	point_init(&B_opp);
	O._inf = 1;
	oppose_point_CE(E,B,&B_opp);
//	bases_t O;
//	bases_init(O);

	if(A->_inf == 1)
	{
		point_set_point(C,B);
		//retourner B (x_b,y_b)
		return;
	}
	if(B->_inf == 1)
	{
		point_set_point(C,A);
		//retourner A (x_a, y_a)
		return;
	}
	if(point_equal(A,&B_opp) == 1)
	{
		point_set_point(C,&O);
		//retourner O
		return;
	}
	if(point_equal(A,B) == 1)
	{
		//retourner double d'un point(P)
		double_point_CE(E,A,C);
	}
	else
	{
		//addition de deux points distincts
		addition_distinct_point_CE(E,A,B,C);
	}
}//addition_point_CE()

void oppose_point_CE (ptr_curve_t E, ptr_point_t A, ptr_point_t C)
{
	bases_add(A->_x,C->_x,C->_x);
	bases_add(A->_x,A->_y,C->_y);
}//oppose_point_CE()

void double_point_CE (ptr_curve_t E, ptr_point_t A, ptr_point_t AA)
{
	bases_t X_inv, lambda;
	bases_t r0, r1, r2;

	//lambda <- x_a + (y_a / x_a) ==> x_a + (y_a * x_a^-1)
	bases_inverse(A->_x,X_inv);
	bases_mul(A->_y,X_inv, r0);
	bases_add(A->_x,r0,lambda);

	//x_aa <- lambda^2 + lambda + E->_a2
	bases_mul(lambda,lambda,r0);
	bases_add(lambda,r0,r1);
	bases_add(r1,E->_a2,AA->_x);

	//y_aa <- x_a^2 + lambda x_aa + x_aa
	bases_mul(A->_x,A->_x,r0);
	bases_mul(AA->_x,lambda,r1);
	bases_add(r0,r1,r2);
	bases_add(r2,AA->_x,AA->_y);

}//double_point_CE()


void multiple_point_CE (ptr_curve_t E, ptr_point_t A, bases_t k, ptr_point_t C)
{
	point_t Q, Q_temp;
	point_init(&Q);
	Q._inf = 1;
	point_init(&Q_temp);
	//point_set_point(&Q,A);
	int i = 0;
	for(i = M - 1; i >= 0; --i)
	{
		double_point_CE(E,&Q,&Q_temp);
		point_set_point(&Q,&Q_temp);
		if(k[i] == 1)
		{
			addition_point_CE(E,&Q,A,&Q_temp);
			point_set_point(&Q,&Q_temp);
		}
	}
	point_set_point(C,&Q);
}//multiple_point_CE()

void init_data_curve(ptr_point_t G, ptr_curve_t E)
{
	//initialisation de la matrice F (utiliser pour l'artihmetique de bases normale)
	bases_mul_F(f);


	//initialisation du point G

	point_init(G);

	mpz_t g_x, g_y;
	mpz_init_set_str(g_x,"0311103c17167564ace77ccb09c681f886ba54ee8",16);
	mpz_init_set_str(g_y,"333ac13c6447f2e67613bf7009daf98c87bb50c7f",16);

	int_to_bases(g_x,G->_x);
	int_to_bases(g_y,G->_y);

	//point_print(&G,"G");

	//initialisation de l'equation

	bases_init(E->_a1);bases_init(E->_a2);bases_init(E->_a3);bases_init(E->_a4);bases_init(E->_a6);

	mpz_t a1, a2, a6;
	mpz_init_set_str(a6,"6645f3cacf1638e139c6cd13ef61734fbc9e3d9fb",16);
	mpz_init_set_ui(a1,1);
	mpz_init_set_ui(a2,1);

	int_to_bases(a1,E->_a1);
	int_to_bases(a2,E->_a2);
	int_to_bases(a6,E->_a6);

}//init_data_curve()

void multiple_addition_point_CE(ptr_curve_t E, bases_t g_bases, ptr_point_t G, bases_t q_bases, ptr_point_t Q, ptr_point_t GQ, ptr_point_t R)
{
	point_t tmp, tmp_temp;
	point_init(&tmp);
	tmp._inf = 1;
	point_init(&tmp_temp);
	//point_set_point(&Q,A);
	int i = 0;
	for(i = M - 1; i >= 0; --i)
	{
		double_point_CE(E,&tmp,&tmp_temp);
		point_set_point(&tmp,&tmp_temp);
		if(g_bases[i] == 1 && q_bases[i] == 0)
		{
			addition_point_CE(E,&tmp,G,&tmp_temp);
			point_set_point(&tmp,&tmp_temp);
		}
		else if(g_bases[i] == 0 && q_bases[i] == 1)
		{
			addition_point_CE(E,&tmp,Q,&tmp_temp);
			point_set_point(&tmp,&tmp_temp);
		}
		else
		{
			addition_point_CE(E,&tmp,GQ,&tmp_temp);
			point_set_point(&tmp,&tmp_temp);
		}
	}
	point_set_point(R,&tmp);
}//multiple_addition_point_CE()
