#include "wordleLayer.h"
#include <iostream>
#include "../core/application.h"

void WordleLayer::onInit()
{
	if(!load_words_into_array("res/WordleAnswersList.txt", m_WordsList, m_WordsListSize)) 
	{
		std::cout << "failed to load wordle words list.\n";
		Application::Get().exit();
	}
}


void WordleLayer::reset() {
	for(int i=0; i<m_WordsListSize; i++)
	{	
		m_WordsList[i].excluded = false;
	}
}