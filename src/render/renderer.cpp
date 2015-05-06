#include	"renderer.h"

#include	<GL/glew.h>
#include	<GLFW/glfw3.h>
#include	<string.h>
#include	"shader.h"


Renderer* Renderer::renderer = NULL;

Renderable::Renderable()
{

}

Renderable::~Renderable()
{

}

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
	decal = new Shader("decal", SHADER_ATTRIB_POS | SHADER_ATTRIB_COL | SHADER_ATTRIB_TEX, SHADER_UNIFORM_TRANSFORM | SHADER_UNIFORM_TEXTURE);
	texture = new Shader("texture", SHADER_ATTRIB_POS | SHADER_ATTRIB_TEX, SHADER_UNIFORM_TRANSFORM | SHADER_UNIFORM_TEXTURE);

	mat3f_identity(modelworld);
	mat3f_identity(inv_modelworld);
	mat3f_identity(worldview);
	mat3f_identity(inv_worldview);

	projection = NULL;
}

Renderer::~Renderer()
{
	// delete shader programs
	delete wireframe;
	delete decal;
	delete texture;
}