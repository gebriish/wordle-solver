#pragma once

struct Window;

class ImGuiLayer
{
public:
	ImGuiLayer();
	~ImGuiLayer();

	void init(const Window&);
	void newFrame();
	void drawFrame(const Window&);
	void cleanup();
};