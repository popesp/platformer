#pragma	once


#include	"vec2f.h"


void verlet2f(vec2f pos, vec2f old, vec2f acc)
{
	vec2f v;

	vec2f_subtractn(v, pos, old);
	vec2f_copy(old, pos);
	vec2f_add(pos, v);
	vec2f_add(pos, acc);
}