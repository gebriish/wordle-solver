#pragma once 
#include "window.h"
#include "../ui/imgui_layer.h"
#include "../renderer/color.h"
#include "../renderer/quad_renderer.h"
#include "../ui/canvas.h"

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
	void onImGui();
	void onEvent(Event& e);

private:
	Color m_ClearColor = color_from_hexcode("000000");
	ImGuiLayer m_ImGuiLayer;
	Canvas m_UiCanvas;
	Window m_Window;
};