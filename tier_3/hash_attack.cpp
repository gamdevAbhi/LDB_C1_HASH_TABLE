#include <chrono>
#include "../tier_2/hash_map/hash_map.hpp"

size_t get_hash_code(int32_t key)
{
    size_t hash_code = std::hash<int32_t>()(key);

    return hash_code;
}

int main()
{
    abstd::hash_map compromise_hash_map;
    abstd::hash_map normal_hash_map;

    size_t final_bucket_size = 16384;
    size_t total_input = final_bucket_size * 0.74; 
    size_t input_number = 0;
    int32_t key = 0;

    while(input_number < total_input)
    {
        if(get_hash_code(key) % final_bucket_size == 0) 
        {
            compromise_hash_map.insert(key, "attack!");
            input_number++;
        }
        
        key++;
    }

    std::chrono::high_resolution_clock::time_point start_time = std::chrono::high_resolution_clock::now();

    compromise_hash_map.get(key - 1);

    std::chrono::high_resolution_clock::time_point end_time = std::chrono::high_resolution_clock::now();
    std::chrono::microseconds compromise_look_up_time = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

    key = 0;
    input_number = 0;

    while(input_number < total_input)
    {
        normal_hash_map.insert(key, "normal");
        input_number++;
        
        key++;
    }
    
    start_time = std::chrono::high_resolution_clock::now();

    normal_hash_map.get(key - 1);

    end_time = std::chrono::high_resolution_clock::now();
    std::chrono::microseconds normal_look_up_time = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    
    std::cout << "compromise hash map look up time : " << compromise_look_up_time.count() << std::endl;
    std::cout << "normal hash map look up time : " << normal_look_up_time.count() << std::endl;
}