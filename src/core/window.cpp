#include	"window.h"

Window::Window()
{
	WindowSettings settings;

	w = NULL;

	title = WINDOW_TITLE " " WINDOW_VERSION;

	gl_major = WINDOW_DEFAULT_GLMAJOR;
	gl_minor = WINDOW_DEFAULT_GLMINOR;

	near = WINDOW_DEFAULT_NEAR;
	far = WINDOW_DEFAULT_FAR;

	settings.width = WINDOW_DEFAULT_WIDTH;
	settings.height = WINDOW_DEFAULT_HEIGHT;
	settings.angle = WINDOW_SETTINGS_DEFAULT_ANGLE;
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
	float ratio, min;

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
	ratio = near * tanf(new_settings->angle * WINDOW_ANGLECONVERT);
	if (new_settings->width < new_settings->height)
	{
		min = (float)new_settings->width / (float)new_settings->height;
		mat4f_frustum(projection, -ratio * min, ratio * min, -ratio, ratio, near, far);
	}
	else
	{
		min = (float)new_settings->height / (float)new_settings->width;
		mat4f_frustum(projection, -ratio, ratio, -ratio * min, ratio * min, near, far);
	}

	// copy over new settings
	settings.width = new_settings->width;
	settings.height = new_settings->height;
	settings.angle = new_settings->angle;
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