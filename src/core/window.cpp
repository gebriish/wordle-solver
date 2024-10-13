#include "window.h"

#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


void initialize_window(Window& window)
{
	glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	window.glfwWindow = glfwCreateWindow(window.width, window.height, window.title, 0, 0);
	if(window.glfwWindow == 0)
	{
		printf("Failed to create GLFWwindow.\n");
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(window.glfwWindow);
	glfwSwapInterval(0);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		printf("Failed to initialize GLAD.\n");
		destroy_window(window);
		return;
	}

	glfwSetWindowUserPointer(window.glfwWindow, &window);

	glfwSetFramebufferSizeCallback(window.glfwWindow, [](GLFWwindow* event_window, int width, int height)
	{
		Window& window = *(Window*)glfwGetWindowUserPointer(event_window);
		window.width  = width;
		window.height = height;

		Event resizeEvent = Event::CreateResizeEvent(width, height);
		window.EventCallback(resizeEvent);
	});


	glfwSetKeyCallback(window.glfwWindow, [](GLFWwindow* event_window, int key, int scancode, int action, int mods)
	{
		Window& window = *(Window*)glfwGetWindowUserPointer(event_window);
		
		Event e = Event::CreateKeyEvent(key, scancode, action, mods);
		window.EventCallback(e);
	});

	glfwSetCursorPosCallback(window.glfwWindow, [](GLFWwindow* event_window, double xpos, double ypos)
	{
		Window& window = *(Window*)glfwGetWindowUserPointer(event_window);

		Event e = Event::CreateCursorMoveEvent(xpos, ypos, xpos - window.cursor.x, ypos - window.cursor.y);
		window.EventCallback(e);
		window.cursor.x = xpos;
		window.cursor.y = ypos;
	});

	glfwSetMouseButtonCallback(window.glfwWindow, [](GLFWwindow* event_window, int button, int action, int mods)
	{
		Window& window = *(Window*)glfwGetWindowUserPointer(event_window);

		Event e = Event::CreateMouseButtonEvent(button, action, mods);
		window.EventCallback(e);
	});

	glfwSetScrollCallback(window.glfwWindow, [](GLFWwindow* event_window, double x, double y)
	{
		Window& window = *(Window*)glfwGetWindowUserPointer(event_window);

		Event e = Event::CreateScrollEvent(x, y);
		window.EventCallback(e);
	});


	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

bool window_should_close(const Window& window)
{
	return glfwWindowShouldClose(window.glfwWindow);
}

void swap_buffer(const Window& window)
{
	glfwSwapBuffers(window.glfwWindow);
	glfwPollEvents();
}

void destroy_window(Window& window)
{
	glfwDestroyWindow(window.glfwWindow);
	glfwTerminate();
}

void clear_viewport(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT);
}

void clear_viewport(const Color& color)
{
	clear_viewport(color.r/255.0f, color.g/255.0f, color.b/255.0f, color.a/255.0f);
}

void set_event_callback(Window &window,const EventCallbackFn& callback)
{
	window.EventCallback = callback;
}