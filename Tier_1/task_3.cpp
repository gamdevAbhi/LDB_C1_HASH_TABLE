#include <iostream>
#include <cstdint>
#include <unordered_map>
#include <string>

bool is_anagram(std::string left_str, std::string right_str)
{
    std::unordered_map<char, int32_t> diff_map;

    for(int i = 0; i < 26; i++) diff_map.emplace('a' + i, 0);

    for(char& c : left_str)
    {
        if(c >= 'A' && c<= 'Z') diff_map['a' + (c - 'A')]++;
        else if(c >= 'a' && c <= 'z') diff_map[c]++; 
    }

    for(char& c : right_str)
    {
        if(c >= 'A' && c<= 'Z') diff_map['a' + (c - 'A')]--;
        else if(c >= 'a' && c <= 'z') diff_map[c]--; 
    }

    for(char c = 'a'; c <= 'z'; c++) if(diff_map[c] != 0) return false;

    return true;
}