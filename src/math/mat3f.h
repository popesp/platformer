#ifndef	MAT3F
#define	MAT3F


#include	<math.h>
#include	"vec2f.h"


#define	MAT3_SIZE							9
#define	MAT3_DIM							3

#define	MAT3_R0								0
#define	MAT3_R1								1
#define	MAT3_R2								2
#define	MAT3_C0								0
#define	MAT3_C1								3
#define	MAT3_C2								6


typedef float mat3f[MAT3_SIZE];


/*	copy matrix
	param:	dst			destination matrix
	param:	src			source matrix
*/
static void mat3f_copy(mat3f dst, mat3f src)
{
	unsigned i;

	for (i = 0; i < MAT3_SIZE; i++)
		dst[i] = src[i];
}


/*	set all matrix elements to 0
	param:	m			matrix to clear
*/
static void mat3f_clear(mat3f m)
{
	unsigned i;

	for (i = 0; i < MAT3_SIZE; i++)
		m[i] = 0.f;
}

/*	set matrix to the identity
	param:	m			matrix to be set
*/
static void mat3f_identity(mat3f m)
{
	m[MAT3_R0 + MAT3_C0] = 1.f;	m[MAT3_R0 + MAT3_C1] = 0.f;	m[MAT3_R0 + MAT3_C2] = 0.f;
	m[MAT3_R1 + MAT3_C0] = 0.f;	m[MAT3_R1 + MAT3_C1] = 1.f;	m[MAT3_R1 + MAT3_C2] = 0.f;
	m[MAT3_R2 + MAT3_C0] = 0.f;	m[MAT3_R2 + MAT3_C1] = 0.f;	m[MAT3_R2 + MAT3_C2] = 1.f;
}


/*	find transpose of matrix (new)
	param:	res			resultant matrix
	param:	m			matrix to find transpose of
*/
static void mat3f_transposen(mat3f res, mat3f m)
{
	res[MAT3_R0 + MAT3_C0] = m[MAT3_R0 + MAT3_C0];
	res[MAT3_R0 + MAT3_C1] = m[MAT3_R1 + MAT3_C0];
	res[MAT3_R0 + MAT3_C2] = m[MAT3_R2 + MAT3_C0];
	res[MAT3_R1 + MAT3_C0] = m[MAT3_R0 + MAT3_C1];
	res[MAT3_R1 + MAT3_C1] = m[MAT3_R1 + MAT3_C1];
	res[MAT3_R1 + MAT3_C2] = m[MAT3_R2 + MAT3_C1];
	res[MAT3_R2 + MAT3_C0] = m[MAT3_R0 + MAT3_C2];
	res[MAT3_R2 + MAT3_C1] = m[MAT3_R1 + MAT3_C2];
	res[MAT3_R2 + MAT3_C2] = m[MAT3_R2 + MAT3_C2];
}

/*	find transpose of matrix
	param:	m			matrix to find transpose of
*/
static void mat3f_transpose(mat3f m)
{
	mat3f n;

	mat3f_transposen(n, m);
	mat3f_copy(m, n);
}


/*	multiply matrix by other matrix (new)
	param:	res			resultant matrix
	param:	m0			matrix multiplicand
	param:	m1			matrix multiplier
*/
static void mat3f_multiplyn(mat3f res, mat3f m0, mat3f m1)
{
	unsigned r, c;

	for (c = 0; c < MAT3_SIZE; c += MAT3_DIM)
		for (r = 0; r < MAT3_DIM; r++)
			res[c + r] =
				m0[r + MAT3_C0] * m1[MAT3_R0 + c] +
				m0[r + MAT3_C1] * m1[MAT3_R1 + c] +
				m0[r + MAT3_C2] * m1[MAT3_R2 + c];
}

/*	multiply matrix by other matrix
	param:	m0			matrix multiplicand
	param:	m1			matrix multiplier
*/
static void mat3f_multiply(mat3f m0, mat3f m1)
{
	mat3f n;

	mat3f_multiplyn(n, m0, m1);
	mat3f_copy(m0, n);
}


/*	set matrix to orthographic projection
	param:	m			matrix to be set
	param:	l			left clipping plane
	param:	r			right clipping plane
	param:	b			bottom clipping plane
	param:	t			top clipping plane
*/
static void mat3f_ortho(mat3f m, float l, float r, float b, float t)
{
	m[MAT3_R0 + MAT3_C0] = 2.f / (r - l);
	m[MAT3_R0 + MAT3_C1] = 0.f;
	m[MAT3_R0 + MAT3_C2] = -(r + l) / (r - l);
	m[MAT3_R1 + MAT3_C0] = 0.f;
	m[MAT3_R1 + MAT3_C1] = 2.f / (t - b);
	m[MAT3_R1 + MAT3_C2] = -(t + b) / (t - b);
	m[MAT3_R2 + MAT3_C0] = 0.f;
	m[MAT3_R2 + MAT3_C1] = 0.f;
	m[MAT3_R2 + MAT3_C2] = 1.f;
}


/*	set matrix to translation transformation
	param:	m			matrix to be set
	param:	x			translation in x-axis
	param:	y			translation in y-axis
*/
static void mat3f_translate(mat3f m, float x, float y)
{
	m[MAT3_R0 + MAT3_C0] = 1.f;	m[MAT3_R0 + MAT3_C1] = 0.f;	m[MAT3_R0 + MAT3_C2] = x;
	m[MAT3_R1 + MAT3_C0] = 0.f;	m[MAT3_R1 + MAT3_C1] = 1.f;	m[MAT3_R1 + MAT3_C2] = y;
	m[MAT3_R2 + MAT3_C0] = 0.f;	m[MAT3_R2 + MAT3_C1] = 0.f;	m[MAT3_R2 + MAT3_C2] = 1.f;
}

/*	multiply matrix by translation transformation (new)
	param:	res			resultant matrix
	param:	m			original matrix
	param:	x			translation in x-axis
	param:	y			translation in y-axis
*/
static void mat3f_translatemuln(mat3f res, mat3f m, float x, float y)
{
	mat3f n;

	mat3f_translate(n, x, y);
	mat3f_multiplyn(res, m, n);
}

/*	multiply matrix by translation transformation
	param:	m			original matrix
	param:	x			translation in x-axis
	param:	y			translation in y-axis
*/
static void mat3f_translatemul(mat3f m, float x, float y)
{
	mat3f n;

	mat3f_translate(n, x, y);
	mat3f_multiply(m, n);
}


/*	set matrix to non-uniform scale transformation
	param:	m			matrix to be set
	param:	x			scale along x-axis
	param:	y			scale along y-axis
*/
static void mat3f_scale(mat3f m, float x, float y)
{
	m[MAT3_R0 + MAT3_C0] = x;	m[MAT3_R0 + MAT3_C1] = 0.f;	m[MAT3_R0 + MAT3_C2] = 0.f;
	m[MAT3_R1 + MAT3_C0] = 0.f;	m[MAT3_R1 + MAT3_C1] = y;	m[MAT3_R1 + MAT3_C2] = 0.f;
	m[MAT3_R2 + MAT3_C0] = 0.f;	m[MAT3_R2 + MAT3_C1] = 0.f;	m[MAT3_R2 + MAT3_C2] = 1.f;
}

/*	multiply matrix by non-uniform scale transformation (new)
	param:	res			resultant matrix
	param:	m			original matrix
	param:	x			scale along x-axis
	param:	y			scale along y-axis
*/
static void mat3f_scalemuln(mat3f res, mat3f m, float x, float y)
{
	mat3f n;

	mat3f_scale(n, x, y);
	mat3f_multiplyn(res, m, n);
}

/*	multiply matrix by non-uniform scale transformation
	param:	m			original matrix
	param:	x			scale along x-axis
	param:	y			scale along y-axis
*/
static void mat3f_scalemul(mat3f m, float x, float y)
{
	mat3f n;

	mat3f_scale(n, x, y);
	mat3f_multiply(m, n);
}


/*	set matrix to rotation
	param:	m			matrix to be set
	param:	angle		angle of rotation in radians
*/
static void mat3f_rotate(mat3f m, float angle)
{
	m[MAT3_R0 + MAT3_C0] = cosf(angle);	m[MAT3_R0 + MAT3_C1] = -sinf(angle);	m[MAT3_R0 + MAT3_C2] = 0.f;
	m[MAT3_R1 + MAT3_C0] = sinf(angle);	m[MAT3_R1 + MAT3_C1] = cosf(angle);		m[MAT3_R1 + MAT3_C2] = 0.f;
	m[MAT3_R2 + MAT3_C0] = 0.f;			m[MAT3_R2 + MAT3_C1] = 0.f;				m[MAT3_R2 + MAT3_C2] = 1.f;
}

/*	multiply matrix by rotation (new)
	param:	res			resultant matrix
	param:	m			original matrix
	param:	angle		angle of rotation in radians
*/
static void mat3f_rotatemuln(mat3f res, mat3f m, float angle)
{
	mat3f n;

	mat3f_rotate(n, angle);
	mat3f_multiplyn(res, m, n);
}

/*	multiply matrix by rotation
	param:	m			original matrix
	param:	angle		angle of rotation in radians
*/
static void mat3f_rotatexmul(mat3f m, float angle)
{
	mat3f n;

	mat3f_rotate(n, angle);
	mat3f_multiply(m, n);
}


/*	find the inverse of a matrix (new)
	param:	res			resultant matrix
	param:	m			original matrix (assumed invertible)
*/
static void mat3f_invertn(mat3f res, mat3f m)
{
	float det;

	// find the matrix determinant
	det =	m[MAT3_R0 + MAT3_C0] * (m[MAT3_R1 + MAT3_C1] * m[MAT3_R2 + MAT3_C2] - m[MAT3_R2 + MAT3_C1] * m[MAT3_R1 + MAT3_C2]) -
			m[MAT3_R0 + MAT3_C1] * (m[MAT3_R1 + MAT3_C0] * m[MAT3_R2 + MAT3_C2] - m[MAT3_R1 + MAT3_C2] * m[MAT3_R2 + MAT3_C0]) +
			m[MAT3_R0 + MAT3_C2] * (m[MAT3_R1 + MAT3_C0] * m[MAT3_R2 + MAT3_C1] - m[MAT3_R1 + MAT3_C1] * m[MAT3_R2 + MAT3_C0]);

	// find the inverse
	res[MAT3_R0 + MAT3_C0] = (m[MAT3_R1 + MAT3_C1] * m[MAT3_R2 + MAT3_C2] - m[MAT3_R2 + MAT3_C1] * m[MAT3_R1 + MAT3_C2]) / det;
	res[MAT3_R0 + MAT3_C1] = -(m[MAT3_R1 + MAT3_C0] * m[MAT3_R2 + MAT3_C2] - m[MAT3_R1 + MAT3_C2] * m[MAT3_R2 + MAT3_C0]) / det;
	res[MAT3_R0 + MAT3_C2] = (m[MAT3_R1 + MAT3_C0] * m[MAT3_R2 + MAT3_C1] - m[MAT3_R1 + MAT3_C1] * m[MAT3_R2 + MAT3_C0]) / det;
	res[MAT3_R1 + MAT3_C0] = -(m[MAT3_R0 + MAT3_C1] * m[MAT3_R2 + MAT3_C2] - m[MAT3_R0 + MAT3_C2] * m[MAT3_R2 + MAT3_C1]) / det;
	res[MAT3_R1 + MAT3_C1] = (m[MAT3_R0 + MAT3_C0] * m[MAT3_R2 + MAT3_C2] - m[MAT3_R0 + MAT3_C2] * m[MAT3_R2 + MAT3_C0]) / det;
	res[MAT3_R1 + MAT3_C2] = -(m[MAT3_R0 + MAT3_C0] * m[MAT3_R2 + MAT3_C1] - m[MAT3_R2 + MAT3_C0] * m[MAT3_R0 + MAT3_C1]) / det;
	res[MAT3_R2 + MAT3_C0] = (m[MAT3_R0 + MAT3_C1] * m[MAT3_R1 + MAT3_C2] - m[MAT3_R0 + MAT3_C2] * m[MAT3_R1 + MAT3_C1]) / det;
	res[MAT3_R2 + MAT3_C1] = -(m[MAT3_R0 + MAT3_C0] * m[MAT3_R1 + MAT3_C2] - m[MAT3_R1 + MAT3_C0] * m[MAT3_R0 + MAT3_C2]) / det;
	res[MAT3_R2 + MAT3_C2] = (m[MAT3_R0 + MAT3_C0] * m[MAT3_R1 + MAT3_C1] - m[MAT3_R1 + MAT3_C0] * m[MAT3_R0 + MAT3_C1]) / det;
}

/*	Find the inverse of a matrix
	param:	m			original matrix (assumed invertible)
*/
static void mat3f_invert(mat3f m)
{
	mat3f n;

	mat3f_invertn(n, m);
	mat3f_copy(m, n);
}


/*	transform a vector by a matrix with translation (new)
	param:	res			resultant vector
	param:	v			vector to be transformed
	param:	m			transformation matrix
*/
static void mat3f_fulltransformvec2fn(vec2f res, vec2f v, mat3f m)
{
	res[X] = m[MAT3_R0 + MAT3_C0] * v[X] + m[MAT3_R0 + MAT3_C1] * v[Y] + m[MAT3_R0 + MAT3_C2];
	res[Y] = m[MAT3_R1 + MAT3_C0] * v[X] + m[MAT3_R1 + MAT3_C1] * v[Y] + m[MAT3_R1 + MAT3_C2];
}

/*	transform a vector by a matrix with translation
	param:	v			vector to be transformed
	param:	m			transformation matrix
*/
static void mat3f_fulltransformvec2f(vec2f v, mat3f m)
{
	vec2f n;

	mat3f_fulltransformvec2fn(n, v, m);
	vec2f_copy(v, n);
}

/*	transform a vector by a matrix without translation (new)
	param:	res			resultant vector
	param:	v			vector to be transformed
	param:	m			transformation matrix
*/
static void mat3f_transformvec2fn(vec2f res, vec2f v, mat3f m)
{
	res[X] = m[MAT3_R0 + MAT3_C0] * v[X] + m[MAT3_R0 + MAT3_C1] * v[Y];
	res[Y] = m[MAT3_R1 + MAT3_C0] * v[X] + m[MAT3_R1 + MAT3_C1] * v[Y];
}

/*	transform a vector by a matrix without translation
	param:	v			vector to be transformed
	param:	m			transformation matrix
*/
static void mat3f_transformvec2f(vec2f v, mat3f m)
{
	vec2f n;

	mat3f_transformvec2fn(n, v, m);
	vec2f_copy(v, n);
}


#endif