#version	140


in		vec2		vertpos;
in		vec4		vertcol;

out		vec4		pass_vertcol;

uniform	mat3		transform;


void main()
{
	pass_vertcol = vertcol;
	gl_Position = vec4(transform * vec3(vertpos, 1.), 1.);
}