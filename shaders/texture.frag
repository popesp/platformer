#version	140


in		vec2		pass_verttex;

out		vec4		frag_color;

uniform	sampler2D	tex;


void main()
{
	frag_color = texture2D(tex, pass_verttex);
}