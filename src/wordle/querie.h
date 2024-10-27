#pragma once
#include <cstdint>
#include <string>

struct Word {
	std::string string;
	bool excluded;
    double score = 0.0;
};

struct FilterQuerie
{
    char word[6];
    uint8_t green 	= 0;
    uint8_t yellow 	= 0;
};

bool create_querie(const std::string& word, const std::string& color, FilterQuerie& q);