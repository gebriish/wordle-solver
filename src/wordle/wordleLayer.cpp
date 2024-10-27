#include "wordleLayer.h"
#include <iostream>
#include <cmath>
#include "../core/application.h"
#include "utils.h"

void WordleLayer::onInit(const char* path)
{
	std::string current;
	std::fill(std::begin(m_TopTen), std::end(m_TopTen), 0);
	
	if(!load_words_into_array(path, m_WordsList, m_WordsListSize)) 
	{
		std::cout << "failed to load wordle words list.\n";
		Application::Get().exit();
	}
	m_FilteredListSize = m_WordsListSize;

	calculate_letter_frequencies();
	calculate_word_scores();
	calculate_top_ten();

}

void WordleLayer::filterWordsList(const FilterQuerie& q)
{
	filter_words_list(this->m_WordsList, this->m_WordsListSize, m_FilteredListSize, q);

	calculate_letter_frequencies();
	calculate_word_scores();
	calculate_top_ten();
}


void WordleLayer::reset() {
	for(int i=0; i<m_WordsListSize; i++)
	{	
		m_WordsList[i].excluded = false;
	}
	m_FilteredListSize = m_WordsListSize;

	calculate_letter_frequencies();
	calculate_word_scores();
	calculate_top_ten();
}

void WordleLayer::calculate_letter_frequencies()
{
	std::fill(std::begin(m_LetterFrequencies), std::end(m_LetterFrequencies), 0);

	for (int i=0; i<m_WordsListSize; i++) {
        auto& word = m_WordsList[i];
        if(word.excluded) continue;
        
        for (char c : word.string) {
            m_LetterFrequencies[c - 'a']++;
        }
    }
}

void WordleLayer::calculate_word_scores()
{
	for (int i=0; i<m_WordsListSize; i++) {
        auto& word = m_WordsList[i];
		score_word(word, m_LetterFrequencies, m_FilteredListSize);
    }
}

void WordleLayer::calculate_top_ten()
{
    for (int i = 0; i < m_WordsListSize; i++)
    {
        auto& word = m_WordsList[i];
        if (word.excluded) continue;

        for (int j = 0; j < 10; j++)
        {
            auto& top_word = m_WordsList[m_TopTen[j]];

            if (top_word.score < word.score)
            {
                for (int k = 9; k > j; k--)
                {
                    m_TopTen[k] = m_TopTen[k - 1];
                }
				
                m_TopTen[j] = i;
                break;
            }
        }
    }
}