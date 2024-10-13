#include "canvas.h"
#include <core/application.h>
#include <core/input.h>



Canvas::Canvas()
{
}


void Canvas::init()
{
	m_PanelRenderer.init("res/panel.vert", "res/panel.frag");
	auto& window = Application::Get().window();
	m_PanelRenderer.resizeViewport(window.width, window.height);

}


void Canvas::cleanup()
{
	m_Panels.clear();
	m_PanelRenderer.cleanup();

}

void Canvas::onUpdate(float deltaTime)
{
}

void Canvas::draw()
{
	m_PanelRenderer.begin();
	ShaderProgram& program = m_PanelRenderer.getProgram();
	for(auto& panel : m_Panels)
	{
		shader_uploda_float(program, "uRadius", panel->rounding);
		m_PanelRenderer.draw((int)panel->position.x, (int)panel->position.y, (int)panel->size.x, (int) panel->size.y, panel->color);
	}
}

void Canvas::onEvent(Event& e)
{
switch (e.type)
	{
		case EventType::RESIZE: {
			m_PanelRenderer.resizeViewport(e.resizeData.width, e.resizeData.height);
			break;
		}

		case EventType::MOUSE_CLICK: {
			auto[x, y] = Input::getCursorPosition();
			if(e.mouseButtonData.action == ActionCode::PRESS)
			{
				for(auto& p : m_Panels)
					if(p->type == PanelType::BUTTON && p->button.state == ButtonState::HOVER)
						p->button.state = ButtonState::CLICK;
			}
			else if(e.mouseButtonData.action == ActionCode::RELEASE)
			{
				for(auto& p : m_Panels)
					if(p->type == PanelType::BUTTON && p->button.state == ButtonState::CLICK)
					{
						bool bounds_check = (p->position.x < x && x < p->position.x + p->size.x) && ( p->position.y < y && y < p->position.y + p->size.y);
						p->button.state = bounds_check ? ButtonState::HOVER : ButtonState::NONE;
					}
			}
			break;
		}

		case EventType::CURSOR_MOVE: {
			float x = e.cursorMoveData.xPos;
			float y = e.cursorMoveData.yPos;
			for(auto& panel : m_Panels)
			{
				bool x_check = panel->position.x < x && x < panel->position.x + panel->size.x;
				bool y_check = panel->position.y < y && y < panel->position.y + panel->size.y;
				if(x_check && y_check)
				{
					if(panel->type == PanelType::BUTTON && panel->button.state == ButtonState::NONE)
						panel->button.state = ButtonState::HOVER;
				}
				else if(panel->type == PanelType::BUTTON && panel->button.state == ButtonState::HOVER)
					panel->button.state = ButtonState::NONE;
			}

			break;
		}
	}
}


//-------------------------------------------------------------------

std::shared_ptr<Panel> Canvas::addFrame()
{
    return createPanel(PanelType::FRAME);
}

std::shared_ptr<Panel> Canvas::addButton()
{
    return createPanel(PanelType::BUTTON);
}

std::shared_ptr<Panel> Canvas::createPanel(PanelType type)
{
    std::shared_ptr<Panel> panel = std::make_shared<Panel>();
    panel->type = type;

	switch (type)
	{
		case PanelType::BUTTON: 
			panel->button.state = ButtonState::NONE;
		break;
	}

    m_Panels.push_back(panel);
    return panel;
}

//-------------------------------------------------------------------
