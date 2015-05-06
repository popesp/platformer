#include	"texture.h"

#include	<GL/glew.h>
#include	<GLFW/glfw3.h>
#include	<FreeImage.h>


#define	TR									0
#define	TG									1
#define	TB									2
#define	TA									3


Texture::Texture()
{
	width = 0;
	height = 0;

	pixels = (pixel*)0;

	glGenTextures(1, &gl_id);
	glBindTexture(GL_TEXTURE_2D, gl_id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

Texture::Texture(unsigned width, unsigned height)
	: Texture()
{
	this->width = width;
	this->height = height;

	pixels = new pixel[width * height];
}

Texture::~Texture()
{
	glDeleteTextures(1, &gl_id);

	if (pixels)
		delete[] pixels;
	pixels = (pixel*)0;
}


unsigned Texture::getGLID()
{
	return gl_id;
}


Texture* Texture::solidDiffuse(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	Texture* texture;

	texture = new Texture(1, 1);

	texture->pixels[0][TR] = r;
	texture->pixels[0][TG] = g;
	texture->pixels[0][TB] = b;
	texture->pixels[0][TA] = a;

	return texture;
}

Texture* Texture::loadTexture(const char* filename)
{
	FREE_IMAGE_FORMAT format;
	FIBITMAP* bmp, *bmp32;
	Texture* texture;

	format = FreeImage_GetFileType(filename, 0);
	if (format == FIF_UNKNOWN)
		format = FreeImage_GetFIFFromFilename(filename);

	// load and convert to 32-bit
	bmp = FreeImage_Load(format, filename, 0);
	bmp32 = FreeImage_ConvertTo32Bits(bmp);
	FreeImage_Unload(bmp);

	texture = new Texture(FreeImage_GetWidth(bmp32), FreeImage_GetHeight(bmp32));
	FreeImage_ConvertToRawBits((unsigned char*)texture->pixels, bmp32, (int)(texture->width * sizeof(pixel)), 32, FI_RGBA_RED_MASK, FI_RGBA_GREEN_MASK, FI_RGBA_BLUE_MASK, 1);
	FreeImage_Unload(bmp32);

	return texture;
}


void Texture::upload()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, gl_id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (int)width, (int)height, 0, GL_BGRA, GL_UNSIGNED_BYTE, pixels);
}