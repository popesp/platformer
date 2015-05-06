#pragma	once


#include	"../math/mat3f.h"
#include	"texture.h"
#include	"shaders/shader.h"


#define	RENDER_MODES						3
#define	RENDER_MODE_POINTS					0
#define	RENDER_MODE_LINESTRIP				1
#define	RENDER_MODE_TRIANGLES				2


class Renderable
{
public:
	float* buf_verts;

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

	Texture* texture;
};


class Renderer
{
public:
	static Renderer* startup();
	static void shutdown();

	void render(Renderable* rb);

private:
	static Renderer* renderer;

	static const unsigned renderModes[RENDER_MODES];

	Shader* wireframe;
	Shader* ssdecal;
	Shader* sstexture;

	mat3f modelworld;
	mat3f inv_modelworld;
	mat3f worldview;
	mat3f inv_worldview;
	mat3f* projection;

	Renderer();
	~Renderer();
};