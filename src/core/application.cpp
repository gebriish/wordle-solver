#include "application.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "input.h"

Application* Application::s_Instance = nullptr;

Application::Application()
{
	s_Instance = this;

	m_Window.title = "wordle solver";
	m_Window.width  = 800;
	m_Window.height = 600;

	initialize_window(m_Window, WINDOWFLAG_RESIZABLE);
	set_event_callback(m_Window, std::bind(&Application::onEvent, this, std::placeholders::_1));	

	m_WordleLayer.onInit();
	m_UiLayer.onInit();
}

Application::~Application()
{
	m_UiLayer.cleanup();
	destroy_window(m_Window);
}

void Application::run()
{
	float begin_time = (float)glfwGetTime();

	while(!window_should_close(m_Window))
	{
		// time taken to render each frame of the application
		float end_time = (float) glfwGetTime();
		float deltaTime = end_time - begin_time;
		begin_time = end_time;
		//---------------------------------------------------

		clear_viewport(0.13, 0.13, 0.13, 1.0);

		this->onUpdate(deltaTime);

		swap_buffer(m_Window);
	}
}

void Application::onEvent(Event& e)
{
	m_UiLayer.onEvent(e);
}

void Application::onUpdate(float dt)
{
	m_UiLayer.onUpdate(dt);
}
