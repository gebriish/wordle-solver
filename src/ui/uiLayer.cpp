#include "uiLayer.h"
#include "../core/input.h"
#include "../core/application.h"

bool open = true;

void UiLayer::onInit()
{
	m_ImGuiLayer.init(Application::Get().window());
	next_guess = Application::Get().wordleLayer().getBestNextGuess();
}

void UiLayer::cleanup()
{
	m_ImGuiLayer.cleanup();
}

void UiLayer::onUpdate(float dt)
{
	static bool input_open = true;
	static char guess[6] = "";

	auto& window = Application::Get().window();
	auto& wordle_layer = Application::Get().wordleLayer();

	m_ImGuiLayer.newFrame();
	
	
	ImGui::Begin("guesses");
	ImVec2 contentRegion = ImGui::GetContentRegionAvail();

	ImGui::PushID(1);
	ImGui::Text("Suggested: ");
	ImGui::SameLine();
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(209/255.0, 109/255.0, 2/255.0, 1.0));
	if(ImGui::Button(next_guess.c_str(), ImVec2(100, 30)))
	{
		for(int i=0; i<5; i++)
			guess[i] = next_guess[i];
		if(!input_open) {
			input_open = true;
		}
		color = "xxxxx";
	}
	
	ImGui::PopStyleColor();
	ImGui::PopID();


	for(int i=0; i<wordle_layer.getWordsListSize(); i++)
	{
		auto& word = wordle_layer.getWordsList()[i];
		if(word.excluded) continue;
		
		if(ImGui::Button(word.string.c_str(), ImVec2(contentRegion.x, 30)))
		{
			for(int i=0; i<5; i++)
				guess[i] = word.string[i];
			if(!input_open) {
				input_open = true;
			}
			color = "xxxxx";
		}
	}
	ImGui::End();


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
				next_guess = wordle_layer.getBestNextGuess();
			}

            ImGui::EndMenu();
        }
		if (ImGui::BeginMenu("Views"))
		{
			if (ImGui::MenuItem("Input", " "))
				input_open = !input_open;

			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}

	ImGui::End();


	if(input_open)
	{
		ImGui::Begin("input", &input_open, ImGuiWindowFlags_NoResize);
		ImVec2 contentRegion = ImGui::GetContentRegionAvail();

		ImGui::InputText(": guess", guess, sizeof(guess));
		ImGui::NewLine();
		for (int i = 0; i < 5; i++) {
			
			ImGui::PushID(i);
			char label[2] = " ";

			if(strlen(guess) >= i)
			{
				label[0] = guess[i];
				label[1] = '\0';
			}

			ImVec4 buttonColor;

			if (color[i] == 'g') {
				buttonColor = ImVec4(0.60, 0.83, 0.14, 1.0); 
			} else if (color[i] == 'y') {
				buttonColor = ImVec4(0.98, 0.74, 0.18, 1.0);
			} else {
				buttonColor = ImVec4(0.13, 0.13, 0.13, 1.0f);
			}

			ImGui::PushStyleColor(ImGuiCol_Button, buttonColor);
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, buttonColor);
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, buttonColor);

			if(ImGui::Button(label, ImVec2(64, 64))) {
				if(color[i] == 'g')
					color[i] = 'y';
				else if(color[i] == 'y')
					color[i] = 'x';
				else
					color[i] = 'g';
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
			if(strlen(guess) == 5)
			{
				std::string word = guess;
				FilterQuerie q;
				create_querie(word, color, q);
				wordle_layer.filterWordsList(q);
				next_guess = wordle_layer.getBestNextGuess();
				color = "xxxxx";
			}
		}
		ImGui::End();
	}

	m_ImGuiLayer.drawFrame(Application::Get().window());
}

void UiLayer::onEvent(const Event &e)
{
}
