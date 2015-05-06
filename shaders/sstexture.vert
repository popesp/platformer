#version	140


in		vec2		vertpos;
in		vec2		verttex;

out		vec2		pass_verttex;

uniform	mat3		transform;


void main()
{
	pass_verttex = verttex;
	gl_Position = vec4(transform * vec3(vertpos, 1.), 1.);
}