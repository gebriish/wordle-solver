#pragma once 
#include "window.h"
#include "../ui/uiLayer.h"
#include "../wordle/wordleLayer.h"

#include <imgui.h>

class Application
{
private:
	static Application* s_Instance;	// Singleton pointer to the application

public:
	Application();
	~Application();

	void run();

	inline static Application& Get() { return *s_Instance; }

	inline Window& window() { return m_Window; }
	inline UiLayer& uiLayer() { return m_UiLayer; }
	inline WordleLayer& wordleLayer() { return m_WordleLayer; }

	inline bool UiWantMouse() const { return ImGui::GetIO().WantCaptureMouse; }
	inline bool UiWantKeyboard() const { return ImGui::GetIO().WantCaptureKeyboard; }

	inline void exit() { close_window(m_Window); }

private:
	void onUpdate(float dt);
	void onEvent(Event& e);

private:
	WordleLayer m_WordleLayer;
	UiLayer m_UiLayer;
	Window m_Window;
};