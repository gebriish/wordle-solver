#pragma once
#include <functional>
#include "event.h"
#include <cstdint>
#include <renderer/color.h>

struct GLFWwindow;

using EventCallbackFn = std::function<void(Event&)>;

struct Window
{
	uint16_t width  = 1280;
	uint16_t height = 800;
	const char* title = "untitled";
	GLFWwindow* glfwWindow;

	struct {
		double x, y;
	} cursor;

	EventCallbackFn EventCallback;
};

void set_event_callback(Window &window,const EventCallbackFn& callback);

void initialize_window(Window& window);
bool window_should_close(const Window& window);
void clear_viewport(float, float, float, float);
void clear_viewport(const Color& color);
void swap_buffer(const Window& window);
void destroy_window(Window& window);
