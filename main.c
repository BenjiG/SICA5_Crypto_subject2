/*
 * main.c
 *
 *  Created on: 7 oct. 2013
 *      Author: sanchez
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gmp.h>
#include "point.h"
#include "courbes.h"
#include "sha_code.h"

#define ERROR -1
#define NERROR 0
#define DEBUG 0



int generate_key(ptr_curve_t E, ptr_point_t G, ptr_point_t Q, bases_t d_bases)
{
	mpz_t n;
	mpz_init(n);
	mpz_ui_pow_ui(n,2,M);

	if(DEBUG)gmp_printf("%Zd\n",n);

	gmp_randstate_t rand_stat;
	gmp_randinit_mt(rand_stat);
	gmp_randseed_ui(rand_stat,time(NULL));

	mpz_t d;
	mpz_init(d);
	mpz_urandomb(d,rand_stat,M);

	if(DEBUG)gmp_printf("%Zd\n",d);


	bases_init(d_bases);
	int_to_bases(d,d_bases);

	point_init(Q);

	multiple_point_CE(E,G,d_bases,Q);
	if(DEBUG)
	{
		bases_print(d_bases);
		printf("\n");
		point_print(Q,"Q");
	}
	char buffer [1024];
	FILE *pub, *priv;
	pub = fopen("./pub.key","w+");
	if(pub != NULL){
		memset(buffer, '\0', sizeof(buffer));
		bases_to_string(Q->_x,buffer);
		fputs(buffer,pub);
		fputs(";",pub);
		memset(buffer, '\0', sizeof(buffer));
		bases_to_string(Q->_y,buffer);
		fputs(buffer,pub);
		fclose(pub);
	}
	else
		return ERROR;

	priv = fopen("./priv.key","w+");
	if(priv != NULL){
		memset(buffer, '\0', sizeof(buffer));
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
		memset(buffer, '\0', sizeof(buffer));
		fgets(buffer,164,pub);
		string_to_bases(Q->_x,buffer);
		if(DEBUG)printf("%s\n",buffer);
		if(DEBUG)bases_print(Q->_x);
		if(DEBUG)printf("\n%d\n",ftell(pub));
		fseek(pub,164,SEEK_SET);
		if(DEBUG)printf("\n%d\n",ftell(pub));
		memset(buffer, '\0', sizeof(buffer));
		fgets(buffer,164,pub);
		string_to_bases(Q->_y,buffer);
		if(DEBUG)printf("%s\n",buffer);
		if(DEBUG)bases_print(Q->_y);
		if(DEBUG)printf("\n");
		fclose(pub);
	}
	else
		return ERROR;

	priv = fopen("./priv.key","r");
	if(priv != NULL){
		memset(buffer, '\0', sizeof(buffer));
		fgets(buffer,164,priv);
		string_to_bases(d_bases,buffer);
		fclose(priv);
	}
	else
		return ERROR;

	return NERROR;
}//read_key()


int get_key(ptr_curve_t E, ptr_point_t G, ptr_point_t Q, bases_t d_bases)
{
	int res;
	if(fopen("./pub.key","r")!=NULL && fopen("./priv.key","r") != NULL)
	{
		printf("\n\tRead key's in progress\n");
		res = read_key(Q,d_bases);
		printf("\tKey's is read\n");
		return res;
	}
	else
	{
		printf("\n\tGenerate key's in progress\n");
		res = generate_key(E,G,Q,d_bases);
		printf("\tKey's is generate\n");
		return res;
	}
}//get_key()

void ECDSA_sign_file (char * path, ptr_curve_t E, ptr_point_t G, ptr_point_t Q, bases_t d_bases, mpz_t r, mpz_t s)
{
	printf("\n\tStrat EC-DSA algo\n");
	mpz_t k_inv, r0, r1, r2, n, d, k, z, x1;
	mpz_init(k_inv);
	mpz_init(r0);
	mpz_init(r1);
	mpz_init(r2);
	mpz_init(s);
	mpz_init(k);
	mpz_init(z);
	mpz_init(x1);
	mpz_init(r);

	bases_t k_bases;
	bases_init(k_bases);

	point_t X;
	point_init(&X);

	//sha-256 de m
	char buffer[65];
	char buffer_M[40];
	mpz_init(n);
	mpz_ui_pow_ui(n,2,M);
	mpz_init(d);
	bases_to_int(d_bases,d);

	mpz_t seed;
	mpz_init_set_str(seed,"85e25bfe5c86226cdb12016f7553f9d0e693a268",16);
	gmp_randstate_t rand_stat;
	gmp_randinit_default(rand_stat);
	gmp_randseed(rand_stat,seed);
	//gmp_randseed_ui(rand_stat,time(NULL));
	//k*G=(x1,y1) (un scalaire fois un point)

	int step_3 = 0;
	while(!step_3)
	{
		mpz_urandomb(k,rand_stat,M);
		if(DEBUG)gmp_printf("%Zd\n",k);
		int_to_bases(k,k_bases);
		multiple_point_CE(E,G,k_bases,&X);

		if(DEBUG)point_print(&X,"X");

		//r=x1 mod n (x1 est transformé en integer)
		bases_to_int(X._x,x1);

		if(DEBUG)gmp_printf("%Zd\n",x1);
		mpz_mod_2exp(r,x1,M);
		if(mpz_cmp_ui(r,0)<=0)
		{
			printf("\tRestart EC-DSA algo because r = 0\n");
			continue;
		}

		if(DEBUG)gmp_printf("r = x1 mod n, r = %Zd\n", r);
		//z = Hex_to_int(sha-256(M))
		sha256_file(path,buffer);
		strncpy(buffer_M,buffer,40);
		mpz_init_set_str(z,buffer_M,16);

		//s= k^-1(z+r*d) mod n (multiplication d'integers)
		mpz_invert(k_inv,k,n);
		mpz_mul(r0,r,d);
		mpz_add(r1,z,r0);
		mpz_mul(r2,k_inv,r1);
		mpz_mod_2exp(s,r2,M);
		//if s = 0 go to step_3
		if(mpz_cmp_ui(s,0)>0)
		{
			step_3 = 1;
		}
		else
		{
			printf("\tRestart EC-DSA algo because s = 0\n");
		}
	}
	printf("\t\thash : sha-256(M) = %s\n", buffer);
	gmp_printf("\t\tz = %Zd\n",z);
	gmp_printf("\t\tr = %Zd\n",r);
	gmp_printf("\t\ts = %Zd\n",s);
	printf("\tEnd EC-DSA algo\n");
}//ECDSA_sign_file()


void ECDSA_verify_sign_file(char * path, ptr_curve_t E, ptr_point_t G, ptr_point_t Q, mpz_t r, mpz_t s)
{
	mpz_t n;
	mpz_init(n);
	mpz_ui_pow_ui(n,2,M);
	if(mpz_cmp(s,n)<0 && mpz_cmp_ui(s,0)>0)
	{
		printf("\t s is in ]0,n-1]\n");
	}
	else
	{
		printf("\t s isn't ]0,n-1]\n");
		printf("\t signature is false\n");
		return;
	}
	if(mpz_cmp(r,n)<0 && mpz_cmp_ui(r,0)>0)
	{
		printf("\t r is in ]0,n-1]\n");
	}
	else
	{
		printf("\t r isn't ]0,n-1]\n");
		printf("\t signature is false\n");
		return;
	}

	//sha-256 de m
	mpz_t z;
	char buffer[65];
	char buffer_M[40];

	//z = Hex_to_int(sha-256(M))
	sha256_file(path,buffer);
	strncpy(buffer_M,buffer,40);
	mpz_init_set_str(z,buffer_M,16);

	/*if(DEBUG)*/gmp_printf("\t\tn = %Zd\n",n);
	/*if(DEBUG)*/gmp_printf("\t\tz = %Zd\n",z);
	/*if(DEBUG)*/gmp_printf("\t\tr = %Zd\n",r);
	/*if(DEBUG)*/gmp_printf("\t\ts = %Zd\n",s);

	//w = s^-1 mod n
	mpz_t w;
	mpz_init(w);
	mpz_invert(w,s,n);

	//u1 = zw mod n & u2 = rw mod n
	mpz_t u1, u2, r0;
	mpz_init(u1);
	mpz_init(u2);
	mpz_init(r0);
	mpz_mul(r0,z,w);
	mpz_mod_2exp(u1,r0,M);
	mpz_mul(r0,r,w);
	mpz_mod_2exp(u2,r0,M);

	//(x1,y1) = u1 G + u2 Q
	point_t R;
	point_init(&R);
	point_t GQ;
	point_init(&GQ);
	addition_point_CE(E,G,Q,&GQ);

	bases_t g_bases, q_bases;
	bases_init(g_bases);
	bases_init(q_bases);
	int_to_bases(u1,g_bases);
	int_to_bases(u2,q_bases);
	/*if(DEBUG)*/gmp_printf("\t\tw = %Zd\n",w);
	/*if(DEBUG)*/gmp_printf("\t\tu1 = %Zd\n",u1);
	/*if(DEBUG)*/gmp_printf("\t\tu2 = %Zd\n",u2);
	multiple_addition_point_CE(E,g_bases,G,q_bases,Q,&GQ,&R);

	//res = R_x1 mod n (if r = res true else false sign)
	mpz_t res, x1;
	mpz_init(res);
	mpz_init(x1);
	bases_to_int(R._x,x1);
	mpz_mod(res,x1,n);

	if(mpz_cmp(res,r) == 0)
	{
		printf("\t signature is true\n");
	}
	else
	{
		printf("\t signature is false\n");
	}
}//ECDSA_verify_sign_file()

int main(int argc, char **argv)
{
	gmp_printf("Start init \n");
	point_t G;
	curve_t E;
	point_t Q;
	bases_t d_bases;
	mpz_t r, s;
	init_data_curve(&G,&E);
	get_key(&E,&G,&Q,d_bases);
	gmp_printf("End init \n");

	gmp_printf("\n\n\nStart ECDSA-sign \n");
	ECDSA_sign_file(/*argv[0]*/"/home/sanchez/Téléchargements/helloworld.cpp.html",&E,&G,&Q,d_bases,r,s);
	gmp_printf("End ECDSA-sign \n");



	gmp_printf("\n\n\nStart ECDSA-verify-sign \n");
	ECDSA_verify_sign_file(/*argv[0]*/"/home/sanchez/Téléchargements/helloworld.cpp.html",&E,&G,&Q,r,s);
	gmp_printf("End ECDSA-verify-sign \n");
	return EXIT_SUCCESS;
}
