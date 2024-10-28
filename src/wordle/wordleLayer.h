#pragma once
#include "../core/event.h"
#include "querie.h"
#include <vector>

#define MAX_WORD_LIST_SIZE 32768

class WordleLayer
{
public:
	void cleanup();

	void reset();

	void onInit(const char* path);
	void filterWordsList(const FilterQuerie& q);
	
	inline uint32_t getLetterFrequency(uint8_t index) const {
		if(index < 26)
			return m_LetterFrequencies[index];
		else return 0;
	}
	inline Word* getWordsList() { return m_WordsList; }
	inline uint32_t getWordsListSize() const { return m_WordsListSize; }
	inline uint32_t getFilteredSize() const { return m_FilteredListSize; }
	inline uint32_t getTopTen(int index) const { 
		if(index <10)	return m_TopTen[index];
		else return 0;
	};

private:
	void calculate_top_ten();
	void calculate_letter_frequencies();
	void calculate_word_scores();

private:
	uint32_t m_FilteredListSize = 0;
	uint32_t m_LetterFrequencies[26];
	Word m_WordsList[MAX_WORD_LIST_SIZE];
	uint32_t m_WordsListSize;
	uint32_t m_TopTen[10];
};