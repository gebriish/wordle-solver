#include "event.h"

Event Event::CreateResizeEvent(int width, int height) {
    Event e(EventType::RESIZE);
    e.resizeData = { width, height };
    return e;
}

Event Event::CreateScrollEvent(double x, double y) {
    Event e(EventType::SCROLL);
    e.scrollData.xScroll = x;
    e.scrollData.yScroll = y;
    return e;
}

Event Event::CreateCursorMoveEvent(double xPos, double yPos, double dx, double dy) {
    Event e(EventType::CURSOR_MOVE);
    e.cursorMoveData = { xPos, yPos , dx, dy};
    return e;
}

Event Event::CreateMouseButtonEvent(int button, int action, int mods) {
    Event e(EventType::MOUSE_CLICK);
    e.mouseButtonData = { button, action, mods };
    return e;
}

Event Event::CreateKeyEvent(int key, int scancode, int action, int mods) {
    Event e(EventType::KEY_CLICK);
    e.keyData = { key, scancode, action, mods };
    return e;
}

Event Event::CreateCharacterEvent(char character)
{
    Event e(EventType::CHARACTER);
    e.charData = { character };
    return e;
}