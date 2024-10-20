#include "input.h"

#include <GLFW/glfw3.h>
#include "application.h"


bool Input::isKeyPressed(int keycode)
{
	auto& window = Application::Get().window();
	return glfwGetKey(window.glfwWindow, keycode) == GLFW_PRESS;
}

bool Input::isMouseButtonPressed(int button)
{
	auto& window = Application::Get().window();
	return glfwGetMouseButton(window.glfwWindow, button) == GLFW_PRESS;
}

std::pair<float,float> Input::getCursorPosition()
{
	double x, y;
	auto& window = Application::Get().window();
	glfwGetCursorPos(window.glfwWindow, &x, &y);
	return std::pair<float,float>{(float)x, (float(y))};
}