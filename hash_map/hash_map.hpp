#ifndef ABSTD_HASH_MAP
#define ABSTD_HASH_MAP

#include <iostream>
#include <string>
#include <cstdint>

namespace abstd
{
    class hash_map
    {
        public:
        hash_map();
        ~hash_map();
        void insert(std::string key, int32_t value);
        int32_t get(std::string key);
        bool erase(std::string key);

        private:
        struct bucket
        {
            enum state {free, occupied};
            
            std::string key;
            int32_t value = 0;
            enum state current_state = free;
        } typedef abstd_bucket;

        abstd_bucket* buckets;
        size_t bucket_size;
        size_t element_size;

        void resize();
        void desize();
        size_t find_slot(std::string key, abstd_bucket::state state);
        void place_entry(std::string key, int32_t value);
        size_t get_hash_code(std::string key); 
    };
}

#endif