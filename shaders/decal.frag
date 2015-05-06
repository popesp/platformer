#version	140


in		vec4		pass_vertcol;
in		vec2		pass_verttex;

out		vec4		frag_color;

uniform	sampler2D	tex;


void main()
{
	frag_color = vec4(pass_vertcol.rgb, pass_vertcol.a * texture2D(tex, pass_verttex).a);
}