#pragma	once


typedef unsigned char pixel[4];


class Texture
{
public:
	Texture();
	Texture(unsigned width, unsigned height);
	~Texture();

	unsigned getGLID();

	static Texture* solidDiffuse(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
	static Texture* loadTexture(const char* filename);

	void upload();

private:
	unsigned width;
	unsigned height;

	pixel* pixels;

	unsigned gl_id;
};