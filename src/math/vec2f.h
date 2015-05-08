#ifndef	VEC2F
#define	VEC2F


#include	<math.h>


#define	X									0
#define	Y									1

#define	U									0
#define	V									1


typedef float vec2f[2];


/*	set vector values
	param:	v			vector to set
	param:	x			x value
	param:	y			y value
*/
static void vec2f_set(vec2f v, float x, float y)
{
	v[X] = x;
	v[Y] = y;
}

/*	copy vector
	param:	dst			destination vector
	param:	src			source vector
*/
static void vec2f_copy(vec2f dst, vec2f src)
{
	dst[X] = src[X];
	dst[Y] = src[Y];
}


/*	add vector to other vector (new)
	param:	res			resultant vector
	param:	v0			vector augend
	param:	v1			vector addend
*/
static void vec2f_addn(vec2f res, vec2f v0, vec2f v1)
{
	res[X] = v0[X] + v1[X];
	res[Y] = v0[Y] + v1[Y];
}

/*	add vector to other vector
	param:	v0			vector augend
	param:	v1			vector addend
*/
static void vec2f_add(vec2f v0, vec2f v1)
{
	vec2f_addn(v0, v0, v1);
}

/*	subtract vector from other vector (new)
	param:	res			resultant vector
	param:	v0			vector minuend
	param:	v1			vector subtrahend
*/
static void vec2f_subtractn(vec2f res, vec2f v0, vec2f v1)
{
	res[X] = v0[X] - v1[X];
	res[Y] = v0[Y] - v1[Y];
}

/*	subtract vector from other vector
	param:	v0			vector minuend
	param:	v1			vector subtrahend
*/
static void vec2f_subtract(vec2f v0, vec2f v1)
{
	vec2f_subtractn(v0, v0, v1);
}

/*	multiply vector with other vector (new)
param:	res			resultant vector
param:	v0			vector multiplicand
param:	v1			vector multiplier
*/
static void vec2f_multiplyn(vec2f res, vec2f v0, vec2f v1)
{
	res[X] = v0[X] * v1[X];
	res[Y] = v0[Y] * v1[Y];
}

/*	multiply vector with other vector
param:	v0			vector multiplicand
param:	v1			vector multiplier
*/
static void vec2f_multiply(vec2f v0, vec2f v1)
{
	vec2f_multiplyn(v0, v0, v1);
}


/*	vector dot product
	param:	v0			first vector
	param:	v1			second vector
	return:	float		dot product of the two input vectors
*/
static float vec2f_dot(vec2f v0, vec2f v1)
{
	return v0[X] * v1[X] + v0[Y] * v1[Y];
}

/*	find squared length of vector
	param:	v			vector to find squared length of
	return:	float		squared length of input vector
*/
static float vec2f_length2(vec2f v)
{
	return vec2f_dot(v, v);
}

/*	find length of vector
	param:	v			vector to find length of
	return:	float		length of input vector
*/
static float vec2f_length(vec2f v)
{
	return sqrtf(vec2f_length2(v));
}


/*	scale vector by a scalar (new)
	param:	res			resultant vector
	param:	v			vector to scale
	param:	s			scalar
*/
static void vec2f_scalen(vec2f res, vec2f v, float s)
{
	res[X] = v[X] * s;
	res[Y] = v[Y] * s;
}

/*	scale vector by a scalar
	param:	v			vector to scale
	param:	s			scalar
*/
static void vec2f_scale(vec2f v, float s)
{
	vec2f_scalen(v, v, s);
}


/*	normalize vector (new)
	param:	res			resultant vector
	param:	v			vector to normalize (assumed length > 0)
*/
static void vec2f_normalizen(vec2f res, vec2f v)
{
	vec2f_scalen(res, v, 1.f / vec2f_length(v));
}

/*	normalize vector
	param:	v			vector to normalize (assumed length > 0)
*/
static void vec2f_normalize(vec2f v)
{
	vec2f_normalizen(v, v);
}


/*	negate vector (new)
	param:	res			resultant vector
	param:	v			vector to negate
*/
static void vec2f_negaten(vec2f res, vec2f v)
{
	res[X] = -v[X];
	res[Y] = -v[Y];
}

/*	negate vector
	param:	v			vector to negate
*/
static void vec2f_negate(vec2f v)
{
	vec2f_negaten(v, v);
}


/*	project vector onto unit vector (new)
	param:	res			resultant vector
	param:	v0			vector to project
	param:	v1			axis of projection (assumed to be unit length)
*/
static void vec2f_projectn(vec2f res, vec2f v0, vec2f v1)
{
	vec2f_scalen(res, v1, vec2f_dot(v0, v1));
}

/*	project vector onto unit vector
	param:	v0			vector to project
	param:	v1			axis of projection (assumed to be unit length)
*/
static void vec2f_project(vec2f v0, vec2f v1)
{
	vec2f_projectn(v0, v0, v1);
}


/*	reflect vector around unit vector (new)
	param:	res			resultant vector
	param:	v0			vector to reflect
	param:	v1			axis of reflection (assumed to be unit length)
*/
static void vec2f_reflectn(vec2f res, vec2f v0, vec2f v1)
{
	float a = 2.f*vec2f_dot(v0, v1);

	res[X] = v1[X] * a - v0[X];
	res[Y] = v1[Y] * a - v0[Y];
}

/*	reflect vector around unit vector
	param:	v0			vector to reflect
	param:	v1			axis of reflection (assumed to be unit length)
*/
static void vec2f_reflect(vec2f v0, vec2f v1)
{
	vec2f_reflectn(v0, v0, v1);
}


#endif