#pragma once 
#include "window.h"
#include "../ui/imguiLayer.h"
#include "../ui/color.h"

class Application
{

private:
	static Application* s_Instance;	

public:
	Application();
	~Application();

	void run();

	inline Window& window() { return m_Window; }
	inline static Application& Get() { return *s_Instance; }

private:
	void onUpdate(float dt);
	void onImGui(float dt);
	void onEvent(Event& e);

private:
	ImGuiLayer m_ImGuiLayer;
	Window m_Window;
};