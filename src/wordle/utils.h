#pragma once

#include <string>
#include <vector>
#include <string>
#include <unordered_map>
#include <cmath>
#include "querie.h"	

void filter_words_list(Word *words, unsigned int size, const FilterQuerie& q);
bool load_words_into_array(const char* path, Word *words, uint32_t& list_size);
std::unordered_map<char, int> calculate_letter_frequency(Word *words, unsigned int size);
float score_word(const std::string& word, const std::unordered_map<char, int>& letter_freq);
std::string select_best_next_guess(Word *words, unsigned int size);