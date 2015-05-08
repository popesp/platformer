#pragma	once


#include	"vec2f.h"


#define	PHYSICSF_INC						0.001f


static void physics2f_verlet(vec2f pos, vec2f old, vec2f acc)
{
	vec2f v;

	vec2f_subtractn(v, pos, old);
	vec2f_copy(old, pos);
	vec2f_add(pos, v);
	vec2f_add(pos, acc);
}


static unsigned physics2f_detect_AABB_AABB(vec2f topleft0, vec2f botright0, vec2f topleft1, vec2f botright1)
{
	if (topleft0[X] > botright1[X])
		return 0;

	if (topleft1[X] > botright0[X])
		return 0;

	if (topleft0[Y] > botright1[Y])
		return 0;

	if (topleft1[Y] > botright0[Y])
		return 0;

	return 1;
}

static unsigned physics2f_detect_line_line(vec2f pos0, vec2f dim0, vec2f pos1, vec2f dim1, float* t, float* u)
{
	vec2f diff;
	float s;

	s = dim0[X] * dim1[X] - dim0[Y] * dim1[X];

	vec2f_subtractn(diff, pos1, pos0);

	// find intersection distances
	*t = (diff[X] * pos1[Y] - diff[Y] * pos1[X]) / s;
	*u = (diff[X] * pos0[Y] - diff[Y] * pos0[X]) / s;

	if (0.f < *t && *t < 1.f && 0.f < *u && *u < 1.f)
		return 1;

	return 0;
}

static unsigned physics2f_detect_sphere_sphere(vec2f center0, float radius0, vec2f center1, float radius1)
{
	vec2f diff;

	vec2f_subtractn(diff, center0, center1);

	if (vec2f_length(diff) < radius0 + radius1)
		return 1;

	return 0;
}

static unsigned physics2f_detect_AABB_point(vec2f topleft, vec2f botright, vec2f pos)
{
	if (pos[X] < topleft[X])
		return 0;

	if (pos[X] > botright[X])
		return 0;

	if (pos[Y] < topleft[X])
		return 0;

	if (pos[Y] > botright[Y])
		return 0;

	return 1;
}

static unsigned physics2f_detect_sphere_point(vec2f center, float radius2, vec2f pos)
{
	vec2f diff;

	vec2f_subtractn(diff, pos, center);

	if (vec2f_length2(diff) < radius2)
		return 1;

	return 0;
}