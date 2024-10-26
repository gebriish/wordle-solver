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
	
	m_FilteredListSize = m_WordsListSize;
}

void WordleLayer::filterWordsList(const FilterQuerie& q)
{
	std::cout << "List size reduced form " << m_FilteredListSize;
	filter_words_list(this->m_WordsList, this->m_WordsListSize, m_FilteredListSize, q, true);
	std::cout << " to " << m_FilteredListSize << '\n';
}

std::string WordleLayer::getBestNextGuess() {
	return select_best_next_guess(m_WordsList, m_WordsListSize);
}


void WordleLayer::reset() {
	m_FilteredListSize = m_WordsListSize;
	for(int i=0; i<m_WordsListSize; i++)
	{	
		m_WordsList[i].excluded = false;
	}
}