/*
 * point.h
 *
 *  Created on: 7 oct. 2013
 *      Author: sanchez
 */

#ifndef POINT_H_
#define POINT_H_

#include <gmp.h>
#include "bases.h"

/**
 * @struct : point_type
 * @brief : define the type point_t
 * @members : coordinates of point _x and _y
 */
typedef struct {
	bases_t _x;
	bases_t _y;
} point_t;

typedef point_t* ptr_point_t;
/**
 * @function : init_point (ptr_point_t P)
 * @brief :  initialize the pointer of members _x and _y in point P
 */
void point_init (ptr_point_t Point);


/**
 * @function : init_point (ptr_point_t P)
 * @brief : clear the pointer of members _x and _y in point P
 */
void point_clear (ptr_point_t Point);


/**
 * @function : print_point (ptr_point_t P)
 * @brief : print the point P
 */
void point_print (ptr_point_t Point, char * name);


#endif /* POINT_H_ */
