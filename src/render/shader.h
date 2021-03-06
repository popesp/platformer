#pragma	once

#include	"renderer.h"


#define	SHADER_ATTRIBS						3
#define	SHADER_ATTRIB_POS					0
#define	SHADER_ATTRIB_COL					1
#define	SHADER_ATTRIB_TEX					2
#define	SHADER_ATTRIBFLAG_POS				(0x00000001 << SHADER_ATTRIB_POS)
#define	SHADER_ATTRIBFLAG_COL				(0x00000001 << SHADER_ATTRIB_COL)
#define	SHADER_ATTRIBFLAG_TEX				(0x00000001 << SHADER_ATTRIB_TEX)

#define	SHADER_UNIFORMS						2
#define	SHADER_UNIFORMFLAG_TRANSFORM		0x00000001
#define	SHADER_UNIFORMFLAG_TEXTURE			0x00000002


static const char* attribName[SHADER_ATTRIBS] = {"vertpos", "vertcol", "verttex"};
static const unsigned attribSize[SHADER_ATTRIBS] = {2, 4, 2};
static const char* uniformName[SHADER_UNIFORMS] = {"transform",	"tex"};


class Renderer;
class Renderable;


class Shader
{
public:
	int uniforms[SHADER_UNIFORMS];

	Shader(const char* name, unsigned flags_attribs, unsigned flags_uniforms);
	~Shader();

	unsigned getGLID();

	void sendUniforms(Renderer* renderer, Renderable* rb);

private:
	unsigned gl_id;

	unsigned flags_attribs;
	unsigned flags_uniforms;

	static unsigned createShader(const char* filename, unsigned type);

	void link();
};