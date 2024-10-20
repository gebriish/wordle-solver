#pragma once

#define MAX_WORD_LIST_SIZE 4096

#include <string>
#include "querie.h"

inline bool word_has(const std::string& word, char c);
void filter_words_list(Word *words, unsigned int size, const FilterQuerie& q);
bool load_words_into_array(const char* path, Word *words, uint32_t& list_size);