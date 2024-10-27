#include "utils.h"
#include "querie.h"

#include <iostream>
#include <fstream>
#include <cstdint>
#include <string>
#include <bitset>

uint32_t create_char_presence(const std::string &word) {
    uint32_t b = 0;
    for(int i=0; i<word.size(); i++)
        b |= 1 << (word[i] - 'a');
    return b;
}
void filter_words_list(Word *words, unsigned int size, uint32_t &f_size, const FilterQuerie& q)
{
    static const uint8_t shifts[] = {1 << 0, 1 << 1, 1 << 2, 1 << 3, 1 << 4};

    uint32_t yellow_char_flags = 0;

    for(int i=0; i<5; i++)
        if(q.yellow & shifts[i])
            yellow_char_flags |= 1 << (q.word[i] - 'a');


    for(int i=0; i<size; i++)
    {
        if(words[i].excluded) continue;

        const std::string& word = words[i].string;
        uint32_t word_presence = create_char_presence(word);

        bool need_to_exclude = false;

        for(int j = 0; j < 5; j++)
        {
            uint8_t shift = shifts[j];

            if(q.green & shift)
            {
                if(word[j] != q.word[j])
                {
                    need_to_exclude = true;
                    break;
                }
            }
            else if(q.yellow & shift)
            {
                if(word[j] == q.word[j] || !(word_presence & 1 << (q.word[j] - 'a')))
                {
                    need_to_exclude = true;
                    break;
                }
            }
        }

        for(int j = 0; j < 5; j++)
        {
            uint8_t shift = shifts[j];

            if((q.green | q.yellow) & shift) continue;

            char grey_char = q.word[j];

            for(int k = 0; k < 5; k++)
            {
                if((q.green) & shifts[k] || (yellow_char_flags & 1 << (q.word[j] - 'a'))) continue;

                if(word[k] == q.word[j])
                {
                    need_to_exclude = true;
                    break;
                }

            }

            if(need_to_exclude) break;
        }

        f_size -= (int) need_to_exclude;
        words[i].excluded = need_to_exclude;
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

void score_word(Word& word, uint32_t *letter_freq, uint32_t freq_sum)
{
    float score = 0.0;
    std::unordered_map<char, bool> seen;
    for (char c : word.string) {
        if (!seen[c]) {
            score += std::log(letter_freq[c - 'a']);
            seen[c] = true;
        }
    }
    word.score = score;
}