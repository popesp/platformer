#pragma	once


class Renderable
{
public:
	float* buf_verts;

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

};