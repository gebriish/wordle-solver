#pragma once
#include <vector>
#include <core/event.h>
#include <renderer/quad_renderer.h>
#include <memory>
#include "elements.h"

class Canvas
{
public:
	Canvas();

	void init();
	void cleanup();

	std::shared_ptr<Panel> addFrame();
	std::shared_ptr<Panel> addButton();

	void onUpdate(float deltaTime);

	void draw();

	inline std::shared_ptr<Panel> GetPanel(int index) { return m_Panels[index]; }

	void onEvent(Event& e);

private:
	std::shared_ptr<Panel> createPanel(PanelType type);
	QuadRenderer m_PanelRenderer;

private:
	std::vector<std::shared_ptr<Panel>> m_Panels;
};