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

	mat3f_identity(transform);

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
	ptr_verts = buf_verts = new float[num_verts * vertsize];

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


void Renderable::vertpos(float x, float y)
{
	vec2f_set(ptr_verts, x, y);
	ptr_verts += attribSize[SHADER_ATTRIB_POS];
}

void Renderable::vertcol(float r, float g, float b, float a)
{
	vec3f_set(ptr_verts, r, g, b);
	ptr_verts[3] = a;
	ptr_verts += attribSize[SHADER_ATTRIB_COL];
}

void Renderable::verttex(float u, float v)
{
	vec2f_set(ptr_verts, u, v);
	ptr_verts += attribSize[SHADER_ATTRIB_TEX];
}

void Renderable::resetBuffer()
{
	ptr_verts = buf_verts;
}


mat3f* Renderable::getTransform()
{
	return &transform;
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

	rb->updateTransform();

	// send program uniforms
	shader->sendUniforms(this, rb);

	glDrawArrays(rb->getMode(), 0, (int)rb->getNumVerts());
}


Renderer::Renderer()
{
	// initialize shader programs
	wireframe = new Shader("wireframe", SHADER_ATTRIBFLAG_POS | SHADER_ATTRIBFLAG_COL, SHADER_UNIFORMFLAG_TRANSFORM);
	decal = new Shader("decal", SHADER_ATTRIBFLAG_POS | SHADER_ATTRIBFLAG_COL | SHADER_ATTRIBFLAG_TEX, SHADER_UNIFORMFLAG_TRANSFORM | SHADER_UNIFORMFLAG_TEXTURE);
	texture = new Shader("texture", SHADER_ATTRIBFLAG_POS | SHADER_ATTRIBFLAG_TEX, SHADER_UNIFORMFLAG_TRANSFORM | SHADER_UNIFORMFLAG_TEXTURE);

	mat3f_identity(worldview);

	projection = NULL;
}

Renderer::~Renderer()
{
	// delete shader programs
	delete wireframe;
	delete decal;
	delete texture;
}