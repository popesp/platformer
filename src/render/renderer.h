#pragma	once


#include	"../math/mat3f.h"
#include	"../math/vec2f.h"
#include	"../math/vec3f.h"
#include	"shader.h"
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
	Shader* currentShader;
	Texture* texture;

	Renderable(unsigned mode, unsigned flags_attribs);
	virtual ~Renderable();

	void allocate(unsigned num_verts);
	void upload();

	unsigned getMode();
	unsigned getVAO();
	unsigned getNumVerts();

	void vertpos(float x, float y);
	void vertcol(float r, float g, float b, float a);
	void verttex(float u, float v);
	void resetBuffer();

	mat3f* getTransform();

	virtual void updateTransform() = 0;

protected:
	mat3f transform;

private:
	float* buf_verts;
	float* ptr_verts;

	unsigned gl_id_mode;
	unsigned gl_id_vao;
	unsigned gl_id_vbo;

	unsigned num_verts;

	unsigned vertsize;

	static void initAttrib(unsigned attrib, int size, unsigned vertsize, int offs);
};


class Renderer
{
public:
	mat3f worldview;
	mat3f* projection;

	Shader* wireframe;
	Shader* decal;
	Shader* texture;

	static Renderer* startup();
	static Renderer* getInstance();
	static void shutdown();

	void render(Renderable* rb);

private:
	static Renderer* renderer;

	static const unsigned renderModes[RENDER_MODES];

	Renderer();
	~Renderer();
};