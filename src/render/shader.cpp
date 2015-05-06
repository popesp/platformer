#include	"shader.h"

#include	<GL/glew.h>
#include	<GLFW/glfw3.h>
#include	<stdio.h>


#define	SHADER_FILEPATH						"shaders/"


const char* Shader::attribName[SHADER_ATTRIBS] =
{
	"vertpos",
	"vertcol",
	"verttex"
};

const char* Shader::uniformName[SHADER_UNIFORMS] =
{
	"transform",
	"texture"
};


void sendtransform(Renderer* renderer, Renderable* rb)
{
	mat3f mvp;

	mat3f_multiplyn(mvp, *renderer->projection, renderer->worldview);
	mat3f_multiply(mvp, renderer->modelworld);

	glUniformMatrix3fv(rb->currentShader->uniforms[0], 1, GL_FALSE, mvp);
}

void sendtexture(Renderer* renderer, Renderable* rb)
{
	(void)renderer;

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, rb->texture->getGLID());

	glUniform1i(rb->currentShader->uniforms[1], 0);
}

void (* const Shader::senduniform[SHADER_UNIFORMS])(Renderer* renderer, Renderable* rb) =
{
	sendtransform,
	sendtexture
};


Shader::Shader(const char* name, unsigned flags_attribs, unsigned flags_uniforms)
{
	unsigned vert, frag, i;
	char filename[256];

	// create shaders
	vert = glCreateShader(GL_VERTEX_SHADER);
	frag = glCreateShader(GL_FRAGMENT_SHADER);

	// create vertex shader
	sprintf(filename, SHADER_FILEPATH "%s.vert", name);
	vert = createShader(filename, GL_VERTEX_SHADER);

	// create fragment shader
	sprintf(filename, SHADER_FILEPATH "%s.frag", name);
	frag = createShader(filename, GL_FRAGMENT_SHADER);

	// create the program
	gl_id = glCreateProgram();
	glAttachShader(gl_id, vert);
	glAttachShader(gl_id, frag);

	this->flags_attribs = flags_attribs;
	this->flags_uniforms = flags_uniforms;

	// bind attribute locations
	for (i = 0; i < SHADER_ATTRIBS; i++)
		if (flags_attribs & (0x00000001 << i))
			glBindAttribLocation(gl_id, i, attribName[i]);

	// link the program
	link();

	// count the number of uniforms
	for (i = 0; i < SHADER_UNIFORMS; i++)
		if (flags_uniforms & (0x00000001 << i))
			uniforms[i] = glGetUniformLocation(gl_id, uniformName[i]);

	// flag shaders for deletion
	glDeleteShader(vert);
	glDeleteShader(frag);
}

Shader::~Shader()
{
	glDeleteProgram(gl_id);
}


unsigned Shader::createShader(const char* filename, unsigned type)
{
	unsigned shader, len;
	char* text;
	FILE* file;
	int result;

	shader = glCreateShader(type);

	// load shader file
	file = fopen(filename, "rb");

	// check if file was loaded
	if (!file)
	{
		printf("Failed to load %s\n", filename);
		return 0;
	}

	// get file length
	fseek(file, 0, SEEK_END);
	len = (unsigned)ftell(file);
	fseek(file, 0, SEEK_SET);

	// copy shader source
	text = new char[len + 1];
	fread(text, sizeof(char), len, file);
	text[len] = 0;

	// close shader file
	fclose(file);

	// compile the source
	glShaderSource(shader, 1, &text, NULL);
	glCompileShader(shader);
	delete[] text;

	// check if compilation succeeded
	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		// get the info log for compilation
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &result);
		text = new char[(size_t)result];
		glGetShaderInfoLog(shader, result, NULL, text);

		printf("%s failed to compile:\n%s\n", filename, text);
		delete[] text;
		return 0;
	}

	return shader;
}

void Shader::link()
{
	char* text;
	int result;

	glLinkProgram(gl_id);

	// check if linking succeeded
	glGetProgramiv(gl_id, GL_LINK_STATUS, &result);
	if (result == GL_FALSE)
	{
		// get the info log for linkage
		glGetProgramiv(gl_id, GL_INFO_LOG_LENGTH, &result);
		text = new char[(size_t)result];
		glGetProgramInfoLog(gl_id, result, NULL, text);

		printf("Failed to link shader program (Program ID: %d):\n%s\n", gl_id, text);
		delete[] text;
	}
}