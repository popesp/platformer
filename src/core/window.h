#ifndef	WINDOW
#define	WINDOW


#include	<gl/glew.h>
#include	<GLFW/glfw3.h>
#include	"../math/mat4f.h"


#define	WINDOW_SETTINGS_FLAG_VSYNC			0x00000001
#define	WINDOW_SETTINGS_FLAG_FULLSCREEN		0x00000002


typedef struct
{
	int width;
	int height;

	float angle;

	int samples;

	unsigned flags;
} WindowSettings;

class Window
{
public:
	GLFWwindow* w;

	mat4f projection;

	Window();
	~Window();

	void applysettings(WindowSettings* new_settings);

private:
	WindowSettings settings;

	const char* title;

	int gl_major;
	int gl_minor;

	float near;
	float far;

	unsigned neednew(WindowSettings* new_settings);
};


#endif