#pragma once
#include "../core/event.h"
#include "querie.h"
#include <vector>

#define MAX_WORD_LIST_SIZE 15000

class WordleLayer
{
public:
	void cleanup();

	void reset();

	void onInit();
	void filterWordsList(const FilterQuerie& q);

	std::string getBestNextGuess();
	inline Word* getWordsList() { return m_WordsList; }
	inline uint32_t getWordsListSize() const { return m_WordsListSize; }

private:
	Word m_WordsList[MAX_WORD_LIST_SIZE];
	uint32_t m_WordsListSize;
};