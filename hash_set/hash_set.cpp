#include "hash_set.hpp"

abstd::hash_set::hash_set() :
bucket_size(8),
element_size(0)
{
    buckets = new abstd_bucket*[bucket_size] {new abstd_bucket()};
}

abstd::hash_set::~hash_set()
{
    delete[] buckets;
}

/// @brief add a value into the hash set
/// @param value 
void abstd::hash_set::add(const std::string_view value)
{
    if(element_size == bucket_size) resize();

    add_bucket(value);

    double current_load = static_cast<double>(element_size) / bucket_size;

    if(current_load >= max_threshold_limit) resize();
    else if(current_load < min_threshold_limit && bucket_size > 8) desize();
}

/// @brief check if the value exist in the hash set
/// @param value 
/// @return 
bool abstd::hash_set::contains(const std::string_view value)
{
    return std::get<2>(find_bucket_info(value)) >= 0;
}

/// @brief remove the value from the hash set
/// @param value 
/// @return the value is deleted successfully or not
bool abstd::hash_set::remove(const std::string_view value)
{
    auto [bucket, parent_bucket, index] = find_bucket_info(value);


    if(bucket == nullptr) return false;

    abstd_bucket* next_bucket = bucket->next_bucket;

    delete bucket;

    if(parent_bucket != nullptr) parent_bucket->next_bucket = next_bucket;
    else buckets[index] = next_bucket;

    element_size--;

    return true;
}

/// @brief double the size of the buckets 
void abstd::hash_set::resize()
{
    size_t old_bucket_size = bucket_size;
    abstd_bucket** old_bucket = buckets;
    bucket_size = bucket_size * 2;
    buckets = new abstd_bucket*[bucket_size];

    populate(old_bucket_size, old_bucket);

    delete[] old_bucket;
}

/// @brief desize the buckets by half
void abstd::hash_set::desize()
{
    size_t old_bucket_size = bucket_size;
    abstd_bucket** old_bucket = buckets;
    bucket_size = bucket_size / 2;
    buckets = new abstd_bucket*[bucket_size];
    
    populate(old_bucket_size, old_bucket);

    delete[] old_bucket;
}

/// @brief populate the new_buckets with the old_bucket
/// @param old_size 
/// @param old_bucket 
void abstd::hash_set::populate(size_t old_size, abstd::hash_set::abstd_bucket** old_bucket)
{
    element_size = 0;

    for(int i = 0; i < old_size; i++) 
    {
        abstd_bucket* bucket = old_bucket[i];

        while(bucket != nullptr)
        {
            if(bucket->is_available()) break;
            add_bucket(bucket->value);
            bucket = bucket->next_bucket;
        }
    }
}

/// @brief finding the occupied bucket and parent_bucket pointer
/// @param value 
/// @return pointer for the bucket and parent_bucket;
std::tuple<abstd::hash_set::abstd_bucket*, abstd::hash_set::abstd_bucket*, size_t> 
abstd::hash_set::find_bucket_info(const std::string_view value)
{
    size_t index = get_hash_code(value) % bucket_size;

    abstd_bucket* bucket = buckets[index];
    abstd_bucket* parent_bucket = nullptr;
    
    while(bucket != nullptr && !bucket->is_available())
    {
        parent_bucket = bucket;
        bucket = bucket->next_bucket;

        if(bucket->value == value && !bucket->is_available())
            return std::tuple<abstd_bucket*, abstd_bucket*, size_t>(bucket, parent_bucket, index);
    }

    return std::tuple<abstd_bucket*, abstd_bucket*, size_t>(nullptr, nullptr, -1);
}

/// @brief the logic of inserting the value into the hash set using chaining
/// @param value 
void abstd::hash_set::add_bucket(const std::string_view value)
{
    size_t index = get_hash_code(value) % bucket_size;

    abstd_bucket* bucket = buckets[index];
    abstd_bucket* parent_bucket = nullptr;

    while(bucket != nullptr)
    {
        if(bucket->value == value) return;
        
        parent_bucket = bucket;
        bucket = bucket->next_bucket;
    }

    if(bucket == nullptr) bucket = new abstd_bucket();

    bucket->set_value(value);
    if(parent_bucket != nullptr) parent_bucket->next_bucket = bucket;
    element_size++;
}

/// @brief custom fnv-1a hash function
/// @param value 
/// @return 
size_t abstd::hash_set::get_hash_code(const std::string_view value)
{
    size_t hash_code = 14695981039346656037ULL;

    for(char c : value)
    {
        hash_code ^= static_cast<size_t>(c);
        hash_code *= 1099511628211ULL;
    }

    return hash_code;
}