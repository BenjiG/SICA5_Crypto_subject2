/*
 * main.c
 *
 *  Created on: 7 oct. 2013
 *      Author: sanchez
 */


#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include "point.h"
#include "courbes.h"

int main(void)
{
	//initialisation de la matrice F (utiliser pour l'artihmetique de bases normale)
	bases_mul_F(f);


	//initialisation du point G
	point_t G;
	point_init(&G);

	mpz_t g_x, g_y;
	mpz_init_set_str(g_x,"0311103c17167564ace77ccb09c681f886ba54ee8",16);
	mpz_init_set_str(g_y,"333ac13c6447f2e67613bf7009daf98c87bb50c7f",16);

	int_to_bases(g_x,G._x);
	int_to_bases(g_y,G._y);

	//point_print(&G,"G");

	//initialisation de l'equation
	curve_t E;
	bases_init(E._a1);bases_init(E._a2);bases_init(E._a3);bases_init(E._a4);bases_init(E._a6);

	mpz_t a1, a2, a6;
	mpz_init_set_str(a6,"6645f3cacf1638e139c6cd13ef61734fbc9e3d9fb",16);
	mpz_init_set_ui(a1,1);
	mpz_init_set_ui(a2,1);

	int_to_bases(a1,E._a1);
	int_to_bases(a2,E._a2);
	int_to_bases(a6,E._a6);


	/**
	 * 	Debut ECDSA -- curve
	 *
	 */
	//initialisation n
	mpz_t n;
	mpz_init(n);
	mpz_ui_pow_ui(n,2,M);

	gmp_printf("%Zd\n",n);

	gmp_randstate_t rand_stat;
	gmp_randinit_default(rand_stat);

	mpz_t d;
	mpz_init(d);
	mpz_urandomb(d,rand_stat,M);

	gmp_printf("%Zd\n",d);

	bases_t d_bases;
	bases_init(d_bases);
	int_to_bases(d,d_bases);

	point_t Q;
	point_init(&Q);

	multiple_point_CE(&E,&G,d_bases,M,&Q);

	point_print(&Q,"Q");


	mpz_t k;
	mpz_init(k);
	mpz_urandomb(k,rand_stat,M);

	gmp_printf("%Zd\n",k);

	bases_t k_bases;
	bases_init(k_bases);
	int_to_bases(k,k_bases);

	point_t X;
	point_init(&X);

	multiple_point_CE(&E,&G,d_bases,M,&X);

	point_print(&X,"X");

	point_t P;
	point_init(&P);


	point_t Result;
	point_init(&Result);




	int i;
	for (i = 0; i < 163; ++i)
	{
		if(i % 7 == 0)
		{
			P._x[i] = 1;
			Q._x[i] = 1;
			P._y[i] = 1;
			Q._y[i] = 1;
		}
		else
		{
			P._x[i] = 0;
			Q._x[i] = 0;
			P._y[i] = 0;
			Q._y[i] = 0;
		}
	}

	point_print(&P, "P");
	point_print(&Q, "Q");
	addition_point_CE(&E,&P,&Q,&Result);
	point_print(&Result, "R");

	oppose_point_CE(&E,&P,&Result);
	point_print(&Result, "R");
	bases_t P_inv;
	bases_inverse(P._x,P_inv);
	bases_mul(P._x,P_inv,Result._x);
	bases_print(P._x);
	printf("\n");
	bases_print(P_inv);
	printf("\n");
	bases_print(Result._x);

	return EXIT_SUCCESS;
}
