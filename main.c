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
#include "sha_code.h"

#define ERROR -1
#define NERROR 0

int generate_key(ptr_curve_t E, ptr_point_t G, ptr_point_t Q, bases_t d_bases)
{
	mpz_t n;
	mpz_init(n);
	mpz_ui_pow_ui(n,2,M);

	//gmp_printf("%Zd\n",n);

	gmp_randstate_t rand_stat;
	gmp_randinit_default(rand_stat);

	mpz_t d;
	mpz_init(d);
	mpz_urandomb(d,rand_stat,M);

	gmp_printf("%Zd\n",d);


	bases_init(d_bases);
	int_to_bases(d,d_bases);

	point_init(Q);

	multiple_point_CE(E,G,d_bases,Q);

	//point_print(&Q,"Q");
	char buffer [1024];
	FILE *pub, *priv;
	pub = fopen("./pub.key","w+");
	if(pub != NULL){
		bases_to_string(Q->_x,buffer);
		fputs(buffer,pub);
		fputs(";",pub);
		bases_to_string(Q->_y,buffer);
		fputs(buffer,pub);
		fclose(pub);
	}
	else
		return ERROR;

	priv = fopen("./priv.key","w+");
	if(priv != NULL){
		bases_to_string(d_bases,buffer);
		fputs(buffer,priv);
		fclose(priv);
	}
	else
		return ERROR;

	return NERROR;
}//generate_key()

int read_key(ptr_point_t Q, bases_t d_bases)
{
	point_init(Q);
	bases_init(d_bases);

	char buffer [1024];
	FILE *pub, *priv;
	pub = fopen("./pub.key","r");
	if(pub != NULL){
		fgets(buffer,163,pub);
		string_to_bases(Q->_x,buffer);
		fgets("",1,pub);
		fgets(buffer,163,pub);
		string_to_bases(Q->_y,buffer);
		fclose(pub);
	}
	else
		return ERROR;

	priv = fopen("./priv.key","r");
	if(priv != NULL){
		fgets(buffer,163,priv);
		string_to_bases(d_bases,buffer);
		fclose(priv);
	}
	else
		return ERROR;

	return NERROR;
}//read_key()


int get_key(ptr_curve_t E, ptr_point_t G, ptr_point_t Q, bases_t d_bases)
{
	if(fopen("./pub.key","r")!=NULL && fopen("./priv.key","r") != NULL)
	{
		return read_key(Q,d_bases);
	}
	else
	{
		return generate_key(E,G,Q,d_bases);
	}
}//get_key()




int main(void)
{
	gmp_printf("Start ECDSA-sign \n");
	//initialisation des données de la courbe (equation, point G, variable f utile au calcul de bases normale)
	point_t G;
	curve_t E;

	point_t Q;
	bases_t d_bases;
	mpz_t d;

	mpz_t n;
	mpz_init(n);
	mpz_ui_pow_ui(n,2,M);



	init_data_curve(&G,&E);
	get_key(&E,&G,&Q,d_bases);



	gmp_randstate_t rand_stat;
	//k*G=(x1,y1) (un scalaire fois un point)
	mpz_t k;
	mpz_init(k);
	mpz_urandomb(k,rand_stat,M);

	gmp_printf("%Zd\n",k);

	bases_t k_bases;
	bases_init(k_bases);
	int_to_bases(k,k_bases);

	point_t X;
	point_init(&X);

	multiple_point_CE(&E,&G,k_bases,&X);

	point_print(&X,"X");

	//r=x1 mod n (x1 est transformé en integer)
	mpz_t x1, r;
	mpz_init(x1);
	mpz_init(r);
	bases_to_int(X._x,x1);

	mpz_mod_2exp(r,x1,M);

	gmp_printf("r = x1 mod n, r = %Zd\n", r);

	//s= k^-1(z+r*d) mod n (multiplication d'integers)
	mpz_t k_inv, r0, r1, r2, s;
	mpz_init(k_inv);
	mpz_init(r0);
	mpz_init(r1);
	mpz_init(r2);
	mpz_init(s);

	mpz_invert(k_inv,k,n);
	mpz_mul(r0,r,d);
	//sha-256 de m
	static  char buffer[65];
	sha256_file("/home/sanchez/workspace/SICA5_Crypto_subject2/sha_code.c",buffer);

	printf("%s\n", buffer);

	mpz_t z;
	mpz_init_set_str(z,buffer,16);

	//gmp_printf("%Zd\n",z);
	mpz_add(r1,z,r0);
	mpz_mul(r2,k_inv,r1);
	mpz_mod_2exp(s,r2,M);

	gmp_printf("%Zd\n",s);

	gmp_printf("End ECDSA-sign \n");

	gmp_printf("\n\nStart ECDSA-verify-sign \n");
	gmp_printf("End ECDSA-verify-sign \n");
	return EXIT_SUCCESS;
}
