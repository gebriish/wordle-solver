#pragma once
#include <renderer/texture.h>

class FontRenderer
{

public:
	unsigned int MAX_BATCH_SIZE = 512;	// characters per batch

public:
	FontRenderer(const char* atlas);
	~FontRenderer();

	void begin();
	void queueText();
	void drawText();

private:
	Texture m_Atlas;
};