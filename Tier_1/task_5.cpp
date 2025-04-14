#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

std::string get_sorted_str(std::string str)
{
    int count[26] = {0};
    std::string sorted_str;

    for(char& c : str) count[c - 'a']++;

    for(int i = 0; i < 26; i++) for(int j = 0; j < count[i]; j++) sorted_str += 'a' + i;

    return std::move(sorted_str);
}

void group_anagrams_str(std::vector<std::string> str_list)
{
    std::unordered_map<std::string, std::vector<std::string>> group;

    for(std::string& str : str_list)
    {
        std::string sorted_str(get_sorted_str(str));

        if(group.find(sorted_str) == group.end()) group[sorted_str] = {};

        group[sorted_str].push_back(str);
    }

    int group_index = 0;

    for(auto& anagrams : group)
    {
        std::cout << "group " << group_index++ << " : ";

        for(std::string& anagram : anagrams.second) std::cout << anagram << " ";

        std::cout << '\n';
    }
}