#include <iostream>
#include <string>
#include <cstdint>

#include "../hash_map/hash_map.hpp"

int main()
{
    abstd::hash_map hash_map;

    hash_map.insert("hello", 12);
    std::cout << hash_map.get("hello");
    hash_map.erase("hello");
    
    return 0;
}