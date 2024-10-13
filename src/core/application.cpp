#include "application.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "input.h"
#include <ui/elements.h>
#include <imgui.h>

Application* Application::s_Instance = nullptr;

std::vector<std::shared_ptr<Panel>> buttons;

Application::Application()
{
	s_Instance = this;

	m_Window.title = "wordle solver";
	m_Window.width = 800;
	m_Window.height = 500;
	initialize_window(m_Window);
	set_event_callback(m_Window, std::bind(&Application::onEvent, this, std::placeholders::_1));	

	m_ImGuiLayer.init(m_Window);	
	m_UiCanvas.init();

	for(int y =0; y<1; y++)
	{
		for(int x = 0; x<5; x++)
		{
			int index = x + y * 5;
			buttons.push_back(m_UiCanvas.addButton());
			buttons[index]->position = {(float) x * 69 + 5, (float) y * 69 + 5};
			buttons[index]->size = {64, 64};
			buttons[index]->position.x += m_Window.width/2.0f - 2.5 * 69;
			buttons[index]->position.y += 64;
			buttons[index]->rounding = 1.0;
		}
	}
	

}

Application::~Application()
{
	m_UiCanvas.cleanup();
	m_ImGuiLayer.cleanup();

	destroy_window(m_Window);
}

void Application::run()
{
	float begin_time = (float)glfwGetTime();

	while(!window_should_close(m_Window))
	{
		float end_time = (float) glfwGetTime();
		float deltaTime = end_time - begin_time;
		begin_time = end_time;

		clear_viewport(m_ClearColor);

		this->onUpdate(deltaTime);

		swap_buffer(m_Window);
	}
}

void Application::onEvent(Event& e)
{
	m_UiCanvas.onEvent(e);
	switch (e.type)
	{
		case EventType::RESIZE: {
			m_Window.width = e.resizeData.width;
			m_Window.height = e.resizeData.height;
			glViewport(0, 0, m_Window.width, m_Window.height);
			break;
		}
	}
}

void Application::onUpdate(float dt)
{
	for(auto& b : buttons)
	{
		if(b->button.state == ButtonState::CLICK)
		{
			if(Input::isMouseButtonPressed(0))
				b->color = color_from_hexcode("b8bb26");
			else if(Input::isMouseButtonPressed(1))
				b->color = color_from_hexcode("fabd2f");
			else
				b->color = color_from_hexcode("282828");
				
			b->button.state = ButtonState::HOVER;
		}
	}

	m_UiCanvas.draw();
}

void Application::onImGui()
{
}