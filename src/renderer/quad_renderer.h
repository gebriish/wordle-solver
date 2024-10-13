#pragma once
#include <cstdint>
#include "shader_program.h"
#include "color.h"

class QuadRenderer
{
public:
	QuadRenderer();
	QuadRenderer(uint16_t w, uint16_t h);
	~QuadRenderer();

	void init(const char*, const char*);
	void begin();
	void draw(int x, int y, int width, int height, const Color& color);
	void draw(int x, int y, int width, int height);

	void resizeViewport(uint16_t x, uint16_t y);

	inline ShaderProgram& getProgram() { return m_Program; }

	void cleanup();	

private:
	unsigned int VAO, VBO, EBO;
	ShaderProgram m_Program;
	struct 
	{
		uint16_t width;
		uint16_t height;
	} m_Viewport;
};