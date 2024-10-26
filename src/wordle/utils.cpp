#include "utils.h"
#include "querie.h"

#include <iostream>
#include <fstream>
#include <cstdint>
#include <string>
#include <bitset>

std::bitset<26> create_char_presence(const std::string& word) {
    std::bitset<26> presence;
    for (char c : word) {
        presence.set(c - 'a');
    }
    return presence;
}

void filter_words_list(Word *words, unsigned int size, uint32_t& filtered_list_size, const FilterQuerie& q, bool exclude) {
    static const uint8_t shifts[] = {1 << 0, 1 << 1, 1 << 2, 1 << 3, 1 << 4};

    std::bitset<26> yellow_chars_presence;

    for (int i = 0; i < 5; i++) {
        if (q.yellow & shifts[i]) {
            yellow_chars_presence.set(q.word[i] - 'a');
        }
    }

    for (unsigned int i = 0; i < size; i++) {
        if (words[i].excluded) continue;

        const std::string& word = words[i].string;
        std::bitset<26> word_presence = create_char_presence(word);

        bool exclude_word = false;

        // Check green and yellow constraints
        for (int j = 0; j < 5; j++) {
            uint8_t shift = shifts[j];

            if (q.green & shift) {
                if (word[j] != q.word[j]) {
                    exclude_word = true;
                    break;
                }
            } else if (q.yellow & shift) {
                if (word[j] == q.word[j] || !word_presence.test(q.word[j] - 'a')) {
                    exclude_word = true;
                    break;
                }
            }
        }

        if (exclude_word) {
            words[i].excluded = exclude;
            filtered_list_size--;
            continue;
        }

        // Check grey constraints
        for (int j = 0; j < 5; j++) {
            if ((q.green | q.yellow) & shifts[j]) continue;

            char grey_char = q.word[j];
            if (!yellow_chars_presence.test(grey_char - 'a') && word_presence.test(grey_char - 'a')) {
                exclude_word = true;
                break;
            }
        }

        if (exclude_word) {
            words[i].excluded = exclude;
            filtered_list_size--;
        }
    }
}


bool load_words_into_array(const char* path, Word *words, uint32_t& list_size)
{
	std::ifstream inputFile(path);
	
	if(!inputFile.is_open())
	{
		return false;
	}

	std::string line;
	list_size = 0;
	while(std::getline(inputFile, line))
	{
		words[list_size].string = line;
		words[list_size].excluded = false;
		list_size++;
	}

	return true;
}


std::unordered_map<char, int> calculate_letter_frequency(Word *words, unsigned int size)
{
    std::unordered_map<char, int> letter_freq;
    for (int i=0; i<size; i++) {
        auto& word = words[i];
        if(word.excluded) continue;
        
        for (char c : word.string) {
            letter_freq[c]++;
        }
    }
    return letter_freq;
}

float score_word(const std::string& word, const std::unordered_map<char, int>& letter_freq)
{
    float score = 0.0;
    std::unordered_map<char, bool> seen;
    for (char c : word) {
        if (!seen[c]) { 
            score += std::log(letter_freq.at(c) + 1);
            seen[c] = true;
        }
    }
    return score;
}

std::string select_best_next_guess(Word *words, unsigned int size)
{
    auto letter_freq = calculate_letter_frequency(words, size);

    std::string best_guess;
    float max_score = -1.0;

    for (int i=0; i<size; i++) {
        auto& word = words[i];
        if (!word.excluded) {
            float score = score_word(word.string, letter_freq);
            if (score > max_score) {
                max_score = score;
                best_guess = word.string;
            }
        }
    }
    return best_guess;
}