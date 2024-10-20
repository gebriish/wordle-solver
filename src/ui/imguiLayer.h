#pragma once

struct Window;

class ImGuiLayer
{
public:
	void init(const Window&);
	void newFrame();
	void drawFrame(const Window&);
	void cleanup();
};
