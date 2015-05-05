#ifndef	WINDOW
#define	WINDOW

#define	_USE_MATH_DEFINES
#include	<math.h>

#include	<gl/glew.h>
#include	<GLFW/glfw3.h>
#include	"../math/mat4f.h"

#define	WINDOW_SETTINGS_FLAG_VSYNC			0x00000001
#define	WINDOW_SETTINGS_FLAG_FULLSCREEN		0x00000002

#define	WINDOW_TITLE						"Platformer"
#define	WINDOW_VERSION						"0.0.1"

#define	WINDOW_DEFAULT_WIDTH				1280
#define	WINDOW_DEFAULT_HEIGHT				800

#define	WINDOW_DEFAULT_GLMAJOR				3
#define	WINDOW_DEFAULT_GLMINOR				1

#define	WINDOW_DEFAULT_NEAR					0.01f
#define	WINDOW_DEFAULT_FAR					1000.f

#define	WINDOW_SETTINGS_DEFAULT_ANGLE		90.f
#define	WINDOW_SETTINGS_DEFAULT_SAMPLES		0
#define	WINDOW_SETTINGS_DEFAULT_FLAGS		(WINDOW_SETTINGS_FLAG_VSYNC)

#define	WINDOW_ANGLECONVERT					((float)M_PI / 360.f)

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