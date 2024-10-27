#pragma once

#include <string>
#include <vector>
#include <string>
#include <unordered_map>
#include <cmath>
#include "querie.h"	

void filter_words_list(Word *words, unsigned int size, uint32_t &f_size, const FilterQuerie& q);
bool load_words_into_array(const char* path, Word *words, uint32_t& list_size);
void score_word(Word& word, uint32_t* letter_freq, uint32_t freq_sum);