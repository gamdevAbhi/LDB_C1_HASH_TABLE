#include <cstdint>
#include <iostream>
#include <string>
#include <unordered_map>

void count_frequency(std::string str)
{
    std::unordered_map<char, int32_t> frequency;

    for(int i = 0; i < 26; i++) frequency.emplace('a' + i, 0);

    for(char& c : str)
    {
        if(c >= 'A' && c<= 'Z') frequency['a' + (c - 'A')]++;
        else if(c >= 'a' && c <= 'z') frequency[c]++; 
    }

    for(char c = 'a'; c <= 'z'; c++)
    {
        if(frequency[c] == 0) continue;
        std::cout << "char : " << c << " " << "frequency : " << frequency[c] << std::endl;
    }
}

int main()
{
    std::string str = "The Quick bRown fOx jumps over the laZy Dog";

    count_frequency(str);

    return 0;
}