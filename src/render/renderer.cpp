#include	"renderer.h"

#include	<GL/glew.h>
#include	<GLFW/glfw3.h>
#include	<string.h>
#include	"shader.h"


static unsigned glmodes[RENDER_MODES] = {GL_POINTS, GL_LINE_STRIP, GL_TRIANGLES};


Renderer* Renderer::renderer = NULL;


Renderable::Renderable(unsigned mode, unsigned flags_attribs)
{
	unsigned i;
	int offs;

	gl_id_mode = glmodes[mode];

	glGenVertexArrays(1, &gl_id_vao);
	glGenBuffers(1, &gl_id_vbo);

	// calculate vertex size
	vertsize = 0;
	for (i = 0; i < SHADER_ATTRIBS; i++)
		if (flags_attribs & (0x00000001 << i))
			vertsize += attribSize[i];

	glBindVertexArray(gl_id_vao);
	glBindBuffer(GL_ARRAY_BUFFER, gl_id_vbo);

	// initialize vertex attributes
	offs = 0;
	for (i = 0; i < SHADER_ATTRIBS; i++)
		if (flags_attribs & (0x00000001 << i))
		{
			initAttrib(i, (int)attribSize[i], vertsize, offs);
			offs += attribSize[i];
		}

	// initialize buffers
	num_verts = 0;
	buf_verts = NULL;

	currentShader = NULL;
	texture = NULL;
}

Renderable::~Renderable()
{
	delete[] buf_verts;

	glDeleteVertexArrays(1, &gl_id_vao);
	glDeleteBuffers(1, &gl_id_vbo);
}


void Renderable::allocate(unsigned num_verts)
{
	this->num_verts = num_verts;

	// reallocate client-side vertex buffer
	delete[] buf_verts;
	buf_verts = new float[num_verts * vertsize];

	// allocate opengl vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, gl_id_vbo);
	glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(sizeof(float) * vertsize * num_verts), NULL, GL_STATIC_DRAW);
}

void Renderable::upload()
{
	glBindBuffer(GL_ARRAY_BUFFER, gl_id_vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, (GLsizeiptr)(sizeof(float) * vertsize * num_verts), buf_verts);
}


unsigned Renderable::getMode()
{
	return gl_id_mode;
}

unsigned Renderable::getVAO()
{
	return gl_id_vao;
}

unsigned Renderable::getNumVerts()
{
	return num_verts;
}


void Renderable::initAttrib(unsigned attrib, int size, unsigned vertsize, int offs)
{
	glEnableVertexAttribArray(attrib);
	glVertexAttribPointer(attrib, size, GL_FLOAT, GL_FALSE, (int)(sizeof(float) * vertsize), (void*)(sizeof(float) * offs));
}


Renderer* Renderer::startup()
{
	if (!renderer)
		renderer = new Renderer();

	return renderer;
}

Renderer* Renderer::getInstance()
{
	return renderer;
}

void Renderer::shutdown()
{
	delete renderer;
	renderer = NULL;
}


void Renderer::render(Renderable* rb)
{
	Shader* shader = rb->currentShader;

	glUseProgram(shader->getGLID());
	glBindVertexArray(rb->getVAO());

	// send program uniforms
	shader->sendUniforms(this, rb);

	glDrawArrays(rb->getMode(), 0, (int)rb->getNumVerts());
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