#include <iostream>
#include <string>
#include <cstdint>

#include "../hash_map/hash_map.hpp"

int main()
{
    abstd::hash_map hash_map;

    hash_map.insert(12, "mango");
    std::cout << hash_map.get(12).value();
    hash_map.remove(12);
    
    return 0;
}