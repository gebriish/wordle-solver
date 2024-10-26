#include "wordleLayer.h"
#include <iostream>
#include <cmath>
#include "../core/application.h"
#include "utils.h"

void WordleLayer::onInit()
{
	std::string current;
	
	if(!load_words_into_array("res/FiveLetterWords.txt", m_WordsList, m_WordsListSize)) 
	{
		std::cout << "failed to load wordle words list.\n";
		Application::Get().exit();
	}
}

void WordleLayer::filterWordsList(const FilterQuerie& q)
{
	filter_words_list(this->m_WordsList, this->m_WordsListSize, q);
}

std::string WordleLayer::getBestNextGuess() {
	return select_best_next_guess(m_WordsList, m_WordsListSize);
}


void WordleLayer::reset() {
	for(int i=0; i<m_WordsListSize; i++)
	{	
		m_WordsList[i].excluded = false;
	}
}