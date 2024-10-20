#include "utils.h"
#include "querie.h"

#include <iostream>
#include <fstream>
#include <cstdint>
#include <string>

inline bool word_has(const std::string& word, char c)
{
    for(int i=0; i<word.size(); i++) {
        if(word[i] == c)
            return true;
    }
    return false;
}

void filter_words_list(Word *words, unsigned int size, const FilterQuerie& q)
{
    static const uint8_t shifts[] = {1 << 0, 1 << 1, 1 << 2, 1 << 3, 1 << 4};

    char yellow_characters[6]  = "     ";

    for(int i=0; i<5; i++)
    {
        if(q.yellow & shifts[i])
            yellow_characters[i] = q.word[i];
    }

    for(int i=0; i<size; i++)
    {
        if(words[i].excluded) continue;

        const std::string& word = words[i].string;

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
                if(word[j] == q.word[j] || !word_has(word, q.word[j]))
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
                if((q.green) & shifts[k] || word_has(yellow_characters, q.word[j])) continue;

                if(word[k] == q.word[j])
                {
                    need_to_exclude = true;
                    break;
                }

            }

            if(need_to_exclude) break;
        }

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