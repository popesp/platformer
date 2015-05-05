#include	"renderer.h"

#include	<GL/glew.h>
#include	<GLFW/glfw3.h>
#include	<string.h>


Renderer* Renderer::renderer = NULL;



Renderer* Renderer::startup()
{
	if (!renderer)
		renderer = new Renderer();

	return renderer;
}

void Renderer::shutdown()
{
	delete renderer;
	renderer = NULL;
}


void Renderer::render(Renderable* rb)
{
	(void)rb;
}


Renderer::Renderer()
{
	// initialize shader programs
	wireframe = new Shader("wireframe", SHADER_ATTRIB_POS | SHADER_ATTRIB_COL, SHADER_UNIFORM_TRANSFORM);
	ssdecal = new Shader("ssdecal", SHADER_ATTRIB_POS | SHADER_ATTRIB_COL | SHADER_ATTRIB_TEX, SHADER_UNIFORM_TRANSFORM | SHADER_UNIFORM_TEXTURE);
	sstexture = new Shader("sstexture", SHADER_ATTRIB_POS | SHADER_ATTRIB_TEX, SHADER_UNIFORM_TRANSFORM | SHADER_UNIFORM_TEXTURE);

	mat4f_identity(modelworld);
	mat4f_identity(inv_modelworld);
	mat4f_identity(worldview);
	mat4f_identity(inv_worldview);

	projection = NULL;
}

Renderer::~Renderer()
{
	// delete shader programs
	delete wireframe;
	delete ssdecal;
	delete sstexture;
}