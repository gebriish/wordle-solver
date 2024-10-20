#pragma once
#include "../core/event.h"
#include "querie.h"
#include "utils.h"

class WordleLayer
{
public:
	void cleanup();

	void reset();

	void onInit();

	inline Word* GetWordsList() { return m_WordsList; }
	inline uint32_t GetWordsListSize() const { return m_WordsListSize; }

private:
	Word m_WordsList[MAX_WORD_LIST_SIZE];
	uint32_t m_WordsListSize;
};