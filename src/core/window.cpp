#include	"window.h"

#define	_USE_MATH_DEFINES
#include	<math.h>


#define	WINDOW_DEFAULT_GLMAJOR				3
#define	WINDOW_DEFAULT_GLMINOR				1

#define	WINDOW_SETTINGS_DEFAULT_SAMPLES		0
#define	WINDOW_SETTINGS_DEFAULT_FLAGS		(WINDOW_SETTINGS_FLAG_VSYNC)


Window::Window(int width, int height, const char* title)
{
	WindowSettings settings;

	w = NULL;

	this->title = title;// WINDOW_TITLE " " WINDOW_VERSION;

	gl_major = WINDOW_DEFAULT_GLMAJOR;
	gl_minor = WINDOW_DEFAULT_GLMINOR;

	settings.width = width;
	settings.height = height;
	settings.samples = WINDOW_SETTINGS_DEFAULT_SAMPLES;
	settings.flags = WINDOW_SETTINGS_DEFAULT_FLAGS;

	applysettings(&settings);
}

Window::~Window()
{
	glfwDestroyWindow(w);
}


void Window::applysettings(WindowSettings* new_settings)
{
	GLFWmonitor* primary;

	// create a new window if needed
	if (neednew(new_settings))
	{
		glfwDestroyWindow(w);

		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, gl_major);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, gl_minor);
		glfwWindowHint(GLFW_SAMPLES, new_settings->samples);

		if (new_settings->flags & WINDOW_SETTINGS_FLAG_FULLSCREEN)
		{
			primary = glfwGetPrimaryMonitor();
			w = glfwCreateWindow(new_settings->width, new_settings->height, title, primary, NULL);
		} else
			w = glfwCreateWindow(new_settings->width, new_settings->height, title, NULL, NULL);

		glfwMakeContextCurrent(w);
	} else
		glfwSetWindowSize(w, new_settings->width, new_settings->height);

	// update opengl viewport
	glViewport(0, 0, new_settings->width, new_settings->height);

	// enable or disable vsync
	if (new_settings->flags & WINDOW_SETTINGS_FLAG_VSYNC)
		glfwSwapInterval(1);
	else
		glfwSwapInterval(0);

	// compute the projection matrix for the window
	mat3f_ortho(projection, 0.f, (float)new_settings->width, (float)new_settings->height, 0.f);

	// copy over new settings
	settings.width = new_settings->width;
	settings.height = new_settings->height;
	settings.samples = new_settings->samples;
	settings.flags = new_settings->flags;
}


unsigned Window::neednew(WindowSettings* new_settings)
{
	if (!w)
		return 1;

	if ((settings.flags & WINDOW_SETTINGS_FLAG_FULLSCREEN) != (new_settings->flags & WINDOW_SETTINGS_FLAG_FULLSCREEN))
		return 1;

	if (new_settings->flags & WINDOW_SETTINGS_FLAG_FULLSCREEN)
	{
		if (settings.width != new_settings->width)
			return 1;

		if (settings.height != new_settings->height)
			return 1;
	}

	if (settings.samples != new_settings->samples)
		return 1;

	return 0;
}