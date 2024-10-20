#include "window.h"

#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


void initialize_window(Window& window, int flag)
{
	glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	glfwWindowHint(GLFW_MAXIMIZED, flag & WINDOWFLAG_MAXIMIZED ? GLFW_TRUE : GLFW_FALSE);
	glfwWindowHint(GLFW_RESIZABLE, flag & WINDOWFLAG_RESIZABLE ? GLFW_TRUE : GLFW_FALSE);

	window.glfwWindow = glfwCreateWindow(window.width, window.height, window.title, 0, 0);
	if(window.glfwWindow == 0)
	{
		printf("Failed to create GLFWwindow.\n");
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(window.glfwWindow);
	glfwSwapInterval(flag & WINDOWFLAG_VSYNC ? 1 : 0);

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

	glfwSetCharCallback(window.glfwWindow, [](GLFWwindow* event_window, unsigned int codepoint) {
		Window& window = *(Window*)glfwGetWindowUserPointer(event_window);

		Event e = Event::CreateCharacterEvent(static_cast<char>(codepoint));
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

void set_render_region(Window& window, int x, int y) {
	window.width = x;
	window.height = y;
	glViewport(0, 0, x, y);
}

void set_event_callback(Window &window,const EventCallbackFn& callback)
{
	window.EventCallback = callback;
}

void close_window(Window& window)
{
	glfwSetWindowShouldClose(window.glfwWindow, GLFW_TRUE);
}