/*
 * courbes.c
 *
 *  Created on: 8 oct. 2013
 *      Author: sanchez
 */

#include <gmp.h>

#include "point.h"
#include "courbes.h"

void addition_distinct_point_CE (int *f, ptr_curve_t E, ptr_point_t A, ptr_point_t B, ptr_point_t C)
{
	bases_t X, Y, X_inv, lambda;
	bases_t r0, r1, r2;
	bases_t val1;
	//X <- x_a + x_b
	bases_add(A->_x,B->_x,X);

	//lambda <- (y_a + y_b) / X ==> lambda <- (y_a + y_b) * X^-1
	bases_add(A->_y,B->_y,Y);
	bases_inverse(X,X_inv);
	bases_mul(Y,X_inv,lambda, f);


	//x_c <- lambda^2 + lambda + X + E->_a2
	bases_mul(lambda,lambda,r0, f);
	bases_add(r0,lambda,r1);
	bases_add(r1,X,r0);
	bases_add(r1,E->_a2,C->_x);

	//y_c <- (lambda+ 1)x_c + lambda x_a + y_a
	mpz_t v;
	mpz_init_set_ui(v,1);
	int_to_bases(v,val1);
	bases_add(lambda,val1,r0);
	bases_mul(r0,C->_x,r1, f);
	bases_mul(lambda,A->_x,r2, f);
	bases_add(r1,r2,r0);
	bases_add(r0,A->_y,C->_y);

}//addition_distinct_point_CE()

void addition_point_CE (int *f, ptr_curve_t E, ptr_point_t A, ptr_point_t B, ptr_point_t C)
{
	point_t O;
	point_t B_opp;

	point_init(&O);
	point_init(&B_opp);
	oppose_point_CE(f,E,B,&B_opp);
//	bases_t O;
//	bases_init(O);

	if(point_equal(A,&O) == 1)
	{
		point_set_point(C,B);
		//retourner B (x_b,y_b)
		return;
	}
	if(point_equal(B,&O) == 1)
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
		double_point_CE(f,E,A,C);
	}
	else
	{
		//addition de deux points distincts
		addition_distinct_point_CE(f,E,A,B,C);
	}
}//addition_point_CE()

void oppose_point_CE (int *f, ptr_curve_t E, ptr_point_t A, ptr_point_t C)
{
	bases_add(A->_x,C->_x,C->_x);
	bases_add(A->_x,A->_y,C->_y);
}//oppose_point_CE()

void double_point_CE (int *f, ptr_curve_t E, ptr_point_t A, ptr_point_t AA)
{
	bases_t X_inv, lambda;
	bases_t r0, r1, r2;

	//lambda <- x_a + (y_a / x_a) ==> x_a + (y_a * x_a^-1)
	bases_inverse(A->_x,X_inv);
	bases_mul(A->_y,X_inv, r0, f);
	bases_add(A->_x,r0,lambda);

	//x_aa <- lambda^2 + lambda + E->_a2
	bases_mul(lambda,lambda,r0,f);
	bases_add(lambda,r0,r1);
	bases_add(r1,E->_a2,AA->_x);

	//y_aa <- x_a^2 + lambda x_aa + x_aa
	bases_mul(A->_x,A->_x,r0,f);
	bases_mul(AA->_x,lambda,r1,f);
	bases_add(r0,r1,r2);
	bases_add(r2,AA->_x,AA->_y);

}//double_point_CE()


void multiple_point_CE (int *f, ptr_curve_t E, ptr_point_t A, int *n, int size_n, ptr_point_t C)
{
	point_t Q, Q_temp;
	point_init(&Q);
	point_init(&Q_temp);
	int i;
	for(i = size_n-1; i >= 0; ++i)
	{
		//Q <- 2Q
		double_point_CE(f,E,&Q,&Q_temp);
		point_set_point(&Q,&Q_temp);
		if(n[i] == 1)
		{
			//Q <- Q + P
			addition_point_CE(f,E,&Q,A,&Q_temp);
			point_set_point(&Q,&Q_temp);
		}
	}
	point_set_point(C,&Q);
}//multiple_point_CE()
