#pragma once
#include "../core/event.h"
#include "../wordle/wordleLayer.h"
#include <string>

#include "imguiLayer.h"
#include <imgui.h>

class UiLayer
{
public:
	void cleanup();

	void onInit();
	void onUpdate(float dt);
	void onEvent(const Event& e);


private:
	void show_letter_frequencies(bool *open, WordleLayer& wordle_layer);
	void show_possible_guesses(bool *open, WordleLayer& wordle_layer, bool &input_open);
	void show_input_box(bool *open, WordleLayer& world_layer);
	void show_suggested_words(bool *open, WordleLayer &wordle_layer, bool &input_open);

private:
	ImGuiLayer m_ImGuiLayer;
	char m_InputGuess[6] = "";
	std::string m_InputColor = "xxxxx";
};
