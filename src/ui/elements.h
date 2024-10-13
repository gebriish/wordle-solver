#pragma once
#include <vector>
#include "../renderer/color.h"


typedef struct {
	float x, y;
} vector2;


enum class PanelType 
{
	FRAME  = 0,
	BUTTON = 1,
};

enum class ButtonState
{
	NONE  = 0,
	HOVER = 1,
	CLICK = 2,
};

struct Panel
{	
	PanelType type;
	vector2 position;
	vector2 size;
	float rounding = 5;
	Color   color = color_from_hexcode("282828");

	union 
	{
		struct {ButtonState state; } button;
	};
};
