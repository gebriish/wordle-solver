#pragma once

enum class EventType
{
	RESIZE      	= 0,
	CURSOR_MOVE 	= 1,
	MOUSE_CLICK 	= 2,
	KEY_CLICK   	= 3,
	SCROLL 			= 4,
};

struct Event
{
	EventType type; 

	union {
        struct { int width, height; } resizeData;  
        struct { double xPos, yPos, Dx, Dy; } cursorMoveData;  
        struct { int button, action, mods; } mouseButtonData; 
        struct { int key, scancode, action, mods; } keyData;
        struct { double xScroll, yScroll; } scrollData;
    };

	Event(EventType eventType) : type(eventType) {}

	static Event CreateResizeEvent(int width, int height);
    static Event CreateScrollEvent(double x, double y);
    static Event CreateCursorMoveEvent(double xPos, double yPos, double dx, double dy);
    static Event CreateMouseButtonEvent(int button, int action, int mods);
    static Event CreateKeyEvent(int key, int scancode, int action, int mods);
};