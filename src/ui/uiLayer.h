#pragma once
#include "../core/event.h"
#include <string>

#include "imguiLayer.h"
#include <imgui.h>

class UiLayer
{
public:
	void cleanup();

	void onInit();
	void onUpdate(float dt);
	void onEvent(const Event& e);

private:
	ImGuiLayer m_ImGuiLayer;
	std::string color = "xxxxx";
};