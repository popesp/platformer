#version	140


in		vec2		vertpos;
in		vec3		vertcol;
in		vec2		verttex;

out		vec3		pass_vertcol;
out		vec2		pass_verttex;

uniform	mat3		transform;


void main()
{
	pass_vertcol = vertcol;
	pass_verttex = verttex;
	gl_Position = vec4(transform * vec3(vertpos, 1.), 1.);
}