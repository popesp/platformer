#pragma	once


#include	"../math/mat3f.h"
#include	"texture.h"


#define	RENDER_MODES						3
#define	RENDER_MODE_POINTS					0
#define	RENDER_MODE_LINESTRIP				1
#define	RENDER_MODE_TRIANGLES				2

#define	RENDER_PROGRAMS						3
#define	RENDER_PROGRAM_WIREFRAME			0x00000001
#define	RENDER_PROGRAM_DECAL				0x00000002
#define	RENDER_PROGRAM_TEXTURE				0x00000004


class Shader;


class Renderable
{
public:
	float* buf_verts;

	Shader* currentShader;
	Texture* texture;

	Renderable();
	Renderable(unsigned mode, unsigned programs);
	~Renderable();

private:
	unsigned gl_id_mode;
	unsigned gl_id_vao;
	unsigned gl_id_vbo;

	unsigned num_verts;

	unsigned index_program;

	unsigned vertsize;
};


class Renderer
{
public:
	mat3f modelworld;
	mat3f inv_modelworld;
	mat3f worldview;
	mat3f inv_worldview;
	mat3f* projection;

	static Renderer* startup();
	static void shutdown();

	void render(Renderable* rb);

private:
	static Renderer* renderer;

	static const unsigned renderModes[RENDER_MODES];

	Shader* wireframe;
	Shader* decal;
	Shader* texture;

	Renderer();
	~Renderer();
};