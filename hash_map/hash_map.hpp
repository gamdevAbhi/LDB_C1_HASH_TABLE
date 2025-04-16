#ifndef ABSTD_HASH_MAP
#define ABSTD_HASH_MAP

#include <iostream>
#include <string>
#include <cstdint>
#include <optional>

constexpr double max_tombstone_limit = 0.50;
constexpr double max_threshold_limit = 0.75;
constexpr double min_threshold_limit = 0.30;

namespace abstd
{
    class hash_map
    {
        public:
        hash_map();
        ~hash_map();
        void insert(int32_t key, const std::string_view value);
        std::optional<std::string> get(int32_t key);
        bool contains(int32_t key);
        bool remove(int32_t key);

        private:
        struct bucket
        {
            enum state {empty, occupied, deleted};
            
            int32_t key;
            std::string value;
            enum state current_state = empty;

            void set_pair(int32_t key, const std::string_view value)
            {
                this->key = key;
                this->value = value;
                
                current_state = state::occupied;
            }

            bool is_available()
            {
                return current_state == state::deleted || current_state == state::empty;
            }
        } typedef abstd_bucket;

        abstd_bucket* buckets;
        size_t bucket_size;
        size_t element_size;
        size_t tombstone_size;

        void resize();
        void desize();
        size_t find_key(int32_t key);
        void place_entry(int32_t key, const std::string_view value);
        size_t get_hash_code(int32_t key); 
    };
}

#endif