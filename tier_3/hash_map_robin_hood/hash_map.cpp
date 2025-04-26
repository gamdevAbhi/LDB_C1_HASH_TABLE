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
    if(element_size == bucket_size) resize();

    place_entry(key, value);

    double current_load = static_cast<double>(element_size) / bucket_size;

    if(current_load >= max_threshold_limit) resize();
    else if(current_load < min_threshold_limit && bucket_size > 8) desize();
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
        element_size--;
        tombstone_size++;

        shift_backward(index + 1);

        if((static_cast<double>(tombstone_size) / bucket_size) >= max_tombstone_limit) desize();
        else if((static_cast<double>(element_size) / bucket_size) < 
        min_threshold_limit && bucket_size > 8) desize();

        return true;
    }
    else return false;
}

void abstd::hash_map::shift_backward(size_t index)
{
    size_t left_slot = index - 1;

    if(left_slot < 0) return;

    size_t new_probe_length = left_slot - buckets[index].ideal_slot;

    if(new_probe_length < buckets[index].probe_length && new_probe_length >= 0) 
    {
        buckets[left_slot].set_pair(buckets[index].key, buckets[index].value, 
        buckets[index].ideal_slot, new_probe_length);

        buckets[index].current_state = abstd_bucket::state::deleted;

        shift_backward(index + 1);
    }
}

void abstd::hash_map::resize()
{
    size_t old_bucket_size = bucket_size;
    abstd_bucket* old_bucket = buckets;
    bucket_size = bucket_size * 2;
    buckets = new abstd_bucket[bucket_size];

    element_size = 0;
    tombstone_size = 0;

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
    tombstone_size = 0;

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
    size_t ideal_slot = get_hash_code(key) % bucket_size;
    
    int32_t current_key = key;
    std::string_view current_value = value;
    size_t current_ideal_slot = ideal_slot;
    size_t current_prob_length = 0;

    while(true)
    {
        size_t current_slot = (current_ideal_slot + current_prob_length) % bucket_size;

        if(!buckets[current_slot].is_available() && buckets[current_slot].probe_length < current_prob_length)
        {
            if(buckets[current_slot].key == current_key)
            {
                buckets[current_slot].set_pair(current_key, current_value, current_ideal_slot, current_prob_length);
                break;
            }

            int32_t swap_key = buckets[current_slot].key;
            std::string_view swap_value = buckets[current_slot].value;
            size_t swap_ideal_slot = buckets[current_slot].ideal_slot;
            size_t swap_current_prob_length = buckets[current_slot].probe_length;

            buckets[current_slot].set_pair(current_key, current_value, current_ideal_slot, current_prob_length);

            current_key = swap_key;
            current_value = swap_value;
            current_ideal_slot = swap_ideal_slot;
            current_prob_length = swap_current_prob_length;
        }
        else if(buckets[current_slot].is_available())
        {
            if(buckets[current_slot].current_state == abstd_bucket::state::deleted) tombstone_size--;

            buckets[current_slot].set_pair(current_key, current_value, current_ideal_slot, current_prob_length);

            element_size++;
            break;
        }

        current_prob_length++;
    }
}

size_t abstd::hash_map::get_hash_code(int32_t key)
{
    size_t hash_code = 14695981039346656037ULL;

    hash_code ^= key;
    hash_code *= 1099511628211ULL;

    return hash_code;
}