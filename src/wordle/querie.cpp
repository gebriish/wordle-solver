#include "querie.h"

bool create_querie(const std::string& word, const std::string& color, FilterQuerie& q)
{
    if(word.size() != 5 || color.size() != 5)
        return false;

    for(uint8_t i=0; i<5; i++)
    {
        q.word[i] = word[i];
        uint8_t flag = 1 << i;

        switch (color[i])
        {
            case 'x':
                continue;
                break;

            case 'y':
                q.yellow |= flag;
                break;

            case 'g':
                q.green |= flag;
                break;

            default:
                return false;
                break;
        }
    }
    q.word[5] = '\0';
    return true;
}