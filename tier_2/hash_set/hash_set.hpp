#ifndef ABSTD_HASH_SET
#define ABSTD_HASH_SET

#include <iostream>
#include <string>
#include <cstdint>
#include <tuple>

constexpr double max_threshold_limit = 0.75;
constexpr double min_threshold_limit = 0.30;

namespace abstd
{
    class hash_set
    {
        public:
        hash_set();
        ~hash_set();
        void add(const std::string_view value);
        bool contains(const std::string_view value);
        bool remove(const std::string_view value);

        struct bucket
        {
            enum state {empty, occupied};

            std::string value;
            enum state current_state = empty;
            bucket* next_bucket;

            void set_value(const std::string_view value)
            {
                this->value = value;
                current_state = state::occupied;
            }

            bool is_available()
            {
                return current_state == state::empty;
            }
        } typedef abstd_bucket;

        private:
        abstd_bucket** buckets;
        size_t bucket_size;
        size_t element_size;

        void resize();
        void desize();
        void populate(size_t old_size, abstd_bucket** old_bucket);
        std::tuple<abstd_bucket*, abstd_bucket*, size_t> find_bucket_info(const std::string_view value);
        void add_bucket(const std::string_view value);
        size_t get_hash_code(const std::string_view value); 
    };
}

#endif