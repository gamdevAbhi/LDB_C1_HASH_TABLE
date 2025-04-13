#include <iostream>
#include <cstdint>
#include <unordered_map>
#include <string>

char first_non_repeating_char(std::string str)
{
    std::string clean_word = "";
    std::unordered_map<char, int32_t> diff_map;

    for(char& c : str)
    {
        if(!isalpha(c)) continue;
        char lower_c = tolower(c);

        if(diff_map.find(lower_c) == diff_map.end()) 
        {
            diff_map[lower_c] = 1;
            clean_word += lower_c;
        }
        else diff_map[lower_c]++;
    }

    for(char& c : clean_word) if(diff_map[c] == 1) return c;

    return '\0';
}