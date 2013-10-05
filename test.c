/*
 * test.c
 *
 *  Created on: 5 oct. 2013
 *      Author: sanchez
 */

#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

int main(void)
{
	 mpz_t x;
	 mpz_t y;
	 mpz_t result;
	 mpz_t result_cp;

	 mpz_init(x);
	 mpz_init(y);
	 mpz_init(result);
	 mpz_init(result_cp);

	 mpz_set_str(x, "412650877539559062731483450512926855", 10);
	 mpz_set_str(y, "3822629008318060962512312671273578748225608876420255", 10);

	 mpz_mul(result, x, y);

	 gmp_printf("\n    %Zd\n*\n    %Zd\n--------------------\n%Zd\n\n", x, y, result);

	 mpz_add(result_cp, result, x);
	 gmp_printf("\n%Zd\n",result_cp);
	 /* free used memory */
	 mpz_clear(x);
	 mpz_clear(y);
	 mpz_clear(result);
	 return EXIT_SUCCESS;
}

