#include "hash_map.hpp"

abstd::hash_map::hash_map() :
bucket_size(8),
element_size(0),
tombstone_size(0)
{
    buckets = new abstd_bucket[bucket_size] {abstd_bucket()};
}

abstd::hash_map::~hash_map()
{
    delete[] buckets;
}

/// @brief insert a pair into the hash map
/// @param key 
/// @param value 
void abstd::hash_map::insert(int32_t key, const std::string_view value)
{
    double current_load = static_cast<double>(element_size) / bucket_size;

    if(current_load >= max_threshold_limit) resize();
    else if(current_load < min_threshold_limit && bucket_size > 8) desize();

    place_entry(key, value);
}

/// @brief return the value which is associated with the key
/// @param key 
/// @return if the key found then it will return the value else return nullopt
std::optional<std::string> abstd::hash_map::get(int32_t key)
{
    size_t index = find_key(key);

    if(index >= 0) return buckets[index].value;
    else return std::nullopt;
}

/// @brief check if the key exist in the hash map
/// @param key 
/// @return 
bool abstd::hash_map::contains(int32_t key)
{
    return find_key(key) >= 0;
}

/// @brief for removing the key from the hash map
/// @param key 
/// @return if the key is deleted successfully or not
bool abstd::hash_map::remove(int32_t key)
{
    size_t index = find_key(key);

    if(index >= 0)
    {
        buckets[index].current_state = abstd_bucket::state::deleted;
        tombstone_size++;

        if((tombstone_size % bucket_size) >= max_tombstone_limit) resize();

        return true;
    }
    else return false;
}

void abstd::hash_map::resize()
{
    size_t old_bucket_size = bucket_size;
    abstd_bucket* old_bucket = buckets;
    bucket_size = bucket_size * 2;
    buckets = new abstd_bucket[bucket_size];

    element_size = 0;

    for(int i = 0; i < old_bucket_size; i++) 
    {
        if(old_bucket[i].current_state != abstd_bucket::state::occupied) continue;

        place_entry(old_bucket[i].key, old_bucket[i].value);
    }

    delete[] old_bucket;
}

void abstd::hash_map::desize()
{
    size_t old_bucket_size = bucket_size;
    abstd_bucket* old_bucket = buckets;
    bucket_size = bucket_size / 2;
    buckets = new abstd_bucket[bucket_size];

    element_size = 0;

    for(int i = 0; i < old_bucket_size; i++) 
    {
        if(old_bucket[i].current_state != abstd_bucket::state::occupied) continue;

        place_entry(old_bucket[i].key, old_bucket[i].value);
    }

    delete[] old_bucket;
}

/// @brief use for finding the occupied key index
/// @param key 
/// @return 
size_t abstd::hash_map::find_key(int32_t key)
{
    size_t index = get_hash_code(key) % bucket_size;

    for(int i = 0; i < bucket_size; ++i)
    {
        size_t linear_probing = (index + i) % bucket_size;

        if(buckets[linear_probing].key == key && !buckets[linear_probing].is_available()) return linear_probing;
        else if(buckets[linear_probing].current_state == abstd_bucket::state::empty) return -1;
    }

    return -1;
}

/// @brief the logic of inserting the pair into the hash map
/// @param key 
/// @param value 
void abstd::hash_map::place_entry(int32_t key, const std::string_view value)
{
    size_t index = get_hash_code(key) % bucket_size;

    for(int i = 0; i < bucket_size; ++i)
    {
        size_t linear_probing = (index + i) % bucket_size;

        if(buckets[linear_probing].key == key &&
        buckets[linear_probing].current_state == abstd_bucket::state::occupied)
        {
            buckets[linear_probing].set_pair(key, value);
            return;
        }
        else if(buckets[linear_probing].is_available())
        {
            buckets[linear_probing].set_pair(key, value);
            element_size++;
            return;
        }
    }
}

size_t abstd::hash_map::get_hash_code(int32_t key)
{
    size_t hash_code = std::hash<int32_t>()(key);

    return hash_code;
}