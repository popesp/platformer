#ifndef	WINDOW
#define	WINDOW


#include	<gl/glew.h>
#include	<GLFW/glfw3.h>
#include	"../math/mat3f.h"

#define	WINDOW_SETTINGS_FLAG_VSYNC			0x00000001
#define	WINDOW_SETTINGS_FLAG_FULLSCREEN		0x00000002



typedef struct
{
	int width;
	int height;

	int samples;

	unsigned flags;
} WindowSettings;

class Window
{
public:
	GLFWwindow* w;

	mat3f projection;

	Window(int width, int height, const char* title);
	~Window();

	void applysettings(WindowSettings* new_settings);

private:
	WindowSettings settings;

	const char* title;

	int gl_major;
	int gl_minor;

	unsigned neednew(WindowSettings* new_settings);
};


#endif