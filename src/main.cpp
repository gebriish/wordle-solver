#include "core/window.h"
#include "ui/imgui_layer.h"
#include <iostream>

void OnEvent(Event& e);

int main(){

	Window window;
	window.title = "wordle solver";
	initialize_window(window);

	ImGuiLayer imguiLayer;
	imguiLayer.init(window);
	
	set_event_callback(window, OnEvent);

	while(!window_should_close(window))
	{
		clear_viewport(color_from_hexcode("131313"));

		imguiLayer.newFrame();
		imguiLayer.drawFrame(window);
		
		swap_buffer(window);
	}

	imguiLayer.cleanup();
	destroy_window(window);

}

void OnEvent(Event& e)
{
	switch (e.type)
	{
		case EventType::RESIZE: {
			break;
		}
	}
}