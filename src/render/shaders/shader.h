#pragma	once


#define	SHADER_ATTRIBS						3
#define	SHADER_ATTRIB_POS					0x00000001
#define	SHADER_ATTRIB_COL					0x00000002
#define	SHADER_ATTRIB_TEX					0x00000004

#define	SHADER_UNIFORMS						2
#define	SHADER_UNIFORM_TRANSFORM			0x00000001
#define	SHADER_UNIFORM_TEXTURE				0x00000002


class Shader
{
public:
	Shader(const char* name, unsigned flags_attribs, unsigned flags_uniforms);
	~Shader();

private:
	static const char* attribName[SHADER_ATTRIBS];
	static const char* uniformName[SHADER_UNIFORMS];

	unsigned gl_id;

	unsigned flags_attribs;
	unsigned flags_uniforms;

	int uniforms[SHADER_UNIFORMS];

	static unsigned createShader(const char* filename, unsigned type);

	void link();
};