#include "uiLayer.h"
#include "../core/input.h"
#include "../core/application.h"

void show_menu_bar(bool &input_open, bool &freq_open, bool &guess_open, bool &suggest_open, Window& window)
{
	static bool open = true;
	ImGui::Begin("Viewport", &open, 
	ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_MenuBar | 
	ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus);
	ImGui::SetWindowPos(ImVec2(0.0, 0.0));
	ImGui::SetWindowSize(ImVec2(window.width, window.height));

	if(ImGui::BeginMenuBar()) {
		if (ImGui::BeginMenu("Solver"))
		{
			if (ImGui::MenuItem("Reset", " ")) { 
				Application::Get().wordleLayer().reset();
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Views"))
		{
			if (ImGui::MenuItem("Input", " "))
				input_open = !input_open;
			if (ImGui::MenuItem("Frequencies", " "))
				freq_open = !freq_open;
			if (ImGui::MenuItem("Guesses", " "))
				guess_open = !guess_open;
			if (ImGui::MenuItem("Suggestions", " "))
				suggest_open = !suggest_open;
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}
	ImGui::End();

}

void UiLayer::onInit()
{
	m_ImGuiLayer.init(Application::Get().window());
}

void UiLayer::cleanup()
{
	m_ImGuiLayer.cleanup();
}

void UiLayer::onUpdate(float dt)
{

	static bool freq_open = true;
	static bool input_open = true;
	static bool guess_open = true;
	static bool suggest_open = true;

	auto& window = Application::Get().window();
	auto& wordle_layer = Application::Get().wordleLayer();

	m_ImGuiLayer.newFrame();

	show_letter_frequencies(&freq_open, wordle_layer);
	show_possible_guesses(&guess_open, wordle_layer, input_open);
	show_input_box(&input_open, wordle_layer);
	show_suggested_words(&suggest_open, wordle_layer, input_open);

	//------------------------(Menu Bar)---------------------------
		show_menu_bar(input_open, freq_open, guess_open, suggest_open, window);
	//--------------------------------------------------------------

	m_ImGuiLayer.drawFrame(Application::Get().window());
}

void UiLayer::onEvent(const Event &e)
{
}

void UiLayer::show_letter_frequencies(bool *open, WordleLayer& wordle_layer)
{
	if(*open)
	{
		ImGui::Begin("Letter frequencies", open);
		static float slider_val = 1.0;
		ImGui::SliderFloat("scale ", &slider_val, 1.0, 20);

		for(int i=0; i<26; i++)
		{
			char letter = char('a' + i);
			ImGui::Text("%c", letter);
			ImGui::SameLine();
			ImGui::PushID(i);
			float p = wordle_layer.getLetterFrequency(i) * slider_val * slider_val/ 50.0;
			if(p == 0)
			{
				ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0, 0, 0, 1.0));
				ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(1.0, 0, 0, 1.0));
				ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.0, 0, 0, 1.0));
			}
			else
			{
				ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1,1,1,1));
				ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(1,1,1,1));
				ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1,1,1,1));
			}
			ImGui::Button(" ", ImVec2(p, 30));
			ImGui::PopStyleColor(3);
			ImGui::SameLine();
			ImGui::Text("%d", wordle_layer.getLetterFrequency(i));
			ImGui::PopID();

		}
		ImGui::End();
	}
}

void UiLayer::show_possible_guesses(bool *open, WordleLayer& wordle_layer, bool &input_open)
{
	if(*open)
	{
		ImGui::Begin("guesses (score on right) ", open);
		ImVec2 contentRegion = ImGui::GetContentRegionAvail();

		for(int i=0; i<wordle_layer.getWordsListSize(); i++)
		{
			auto& word = wordle_layer.getWordsList()[i];
			if(word.excluded) continue;
			
			if(ImGui::Button((word.string + ": " + std::to_string(word.score)).c_str(), ImVec2(contentRegion.x, 30)))
			{
				strcpy(m_InputGuess, word.string.c_str());
				if(!input_open) {
					input_open = true;
				}
				m_InputColor = "xxxxx";
			}
		}
		ImGui::End();
	}
}

void UiLayer::show_suggested_words(bool *open, WordleLayer &wordle_layer, bool &input_open)
{
	if(*open)
	{
		ImGui::Begin("Suggested");
		ImGui::Text("out of %d words: ", wordle_layer.getFilteredSize());
		auto content = ImGui::GetContentRegionAvail();
		for(int i=0; i<10 && i < wordle_layer.getFilteredSize(); i++)
		{
			auto& word = wordle_layer.getWordsList()[wordle_layer.getTopTen(i)];
			ImGui::PushID(i);
			if(ImGui::Button((std::to_string(i + 1) + ") " + word.string).c_str(), ImVec2(content.x, 30)))
			{
				strcpy(m_InputGuess, word.string.c_str());
				if(!input_open)
					input_open = true;
				m_InputColor = "xxxxx";
			}
			ImGui::PopID();
		}
		ImGui::End();
	}
}


void UiLayer::show_input_box(bool *open, WordleLayer& wordle_layer)
{
	if(*open)
	{
		ImGui::Begin("input", open, ImGuiWindowFlags_NoResize);
		ImVec2 contentRegion = ImGui::GetContentRegionAvail();

		ImGui::InputText(": guess", m_InputGuess, sizeof(m_InputGuess));
		ImGui::NewLine();
		for (int i = 0; i < 5; i++) {
			
			ImGui::PushID(i);
			char label[2] = " ";

			if(strlen(m_InputGuess) >= i)
			{
				label[0] = m_InputGuess[i];
				label[1] = '\0';
			}

			ImVec4 buttonColor;

			if (m_InputColor[i] == 'g') {
				buttonColor = ImVec4(0.60, 0.83, 0.14, 1.0); 
			} else if (m_InputColor[i] == 'y') {
				buttonColor = ImVec4(0.98, 0.74, 0.18, 1.0);
			} else {
				buttonColor = ImVec4(0.13, 0.13, 0.13, 1.0f);
			}

			ImGui::PushStyleColor(ImGuiCol_Button, buttonColor);
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, buttonColor);
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, buttonColor);

			if(ImGui::Button(label, ImVec2(64, 64))) {
				if(m_InputColor[i] == 'g')
					m_InputColor[i] = 'y';
				else if(m_InputColor[i] == 'y')
					m_InputColor[i] = 'x';
				else
					m_InputColor[i] = 'g';
			}

			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
			ImGui::PopStyleColor();

			ImGui::SameLine();
			ImGui::PopID();
		}

		ImGui::NewLine();
		ImGui::NewLine();

		ImGui::SetCursorPosX(contentRegion.x/2 - 50);
		if (ImGui::Button("Okay", ImVec2(100, 30))) {
			if(strlen(m_InputGuess) == 5)
			{
				std::string word = m_InputGuess;
				FilterQuerie q;
				create_querie(word, m_InputColor, q);
				wordle_layer.filterWordsList(q);
				m_InputColor = "xxxxx";
			}
		}

		ImGui::End();
	}
}