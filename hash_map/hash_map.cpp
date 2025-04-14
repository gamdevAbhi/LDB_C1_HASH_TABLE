#include "hash_map.hpp"

abstd::hash_map::hash_map() :
bucket_size(8),
element_size(0)
{
    buckets = new abstd_bucket[bucket_size];

    for(int i = 0; i < bucket_size; i++) buckets[i] = abstd_bucket();
}

abstd::hash_map::~hash_map()
{
    delete[] buckets;
}

void abstd::hash_map::insert(std::string key, int32_t value)
{
    place_entry(key, value);
    
    double load_factor = static_cast<double>(element_size) / bucket_size;

    if(load_factor >= 0.7) resize();
    else if(load_factor < 0.3 && bucket_size > 8) desize();
}

int32_t abstd::hash_map::get(std::string key)
{
    size_t index = find_slot(key, abstd_bucket::state::occupied);
    return buckets[index].value;
}

bool abstd::hash_map::erase(std::string key)
{
    try
    {
        size_t index = find_slot(key, abstd_bucket::state::occupied);

        buckets[index].current_state = abstd_bucket::state::free;
        return true;
    }
    catch(const std::exception& ex)
    {
        return false;
    }
}

void abstd::hash_map::resize()
{
    size_t old_bucket_size = bucket_size;
    abstd_bucket* old_bucket = buckets;
    bucket_size = bucket_size * 2;
    buckets = new abstd_bucket[bucket_size];

    element_size = 0;

    for(int i = 0; i < old_bucket_size; i++) place_entry(old_bucket[i].key, old_bucket[i].value);

    delete[] old_bucket;
}

void abstd::hash_map::desize()
{
    size_t old_bucket_size = bucket_size;
    abstd_bucket* old_bucket = buckets;
    bucket_size = bucket_size / 2;
    buckets = new abstd_bucket[bucket_size];

    element_size = 0;

    for(int i = 0; i < old_bucket_size; i++) place_entry(old_bucket[i].key, old_bucket[i].value);

    delete[] old_bucket;
}

size_t abstd::hash_map::find_slot(std::string key, abstd_bucket::state state)
{
    size_t hash_code = get_hash_code(key) % bucket_size;

    for(int i = 0; i < bucket_size; ++i)
    {
        size_t index = (hash_code + i) % bucket_size;

        if(buckets[index].key == key &&
        buckets[index].current_state == state) return index; 
    }

    throw std::out_of_range("element not found");
}

void abstd::hash_map::place_entry(std::string key, int32_t value)
{
    size_t hash_code = get_hash_code(key) % bucket_size;

    for(int i = 0; i < bucket_size; ++i)
    {
        size_t index = (hash_code + i) % bucket_size;

        if(buckets[index].current_state == abstd_bucket::state::free ||
        buckets[index].key == key)
        {
            buckets[index].key = key;
            buckets[index].value = value;
            buckets[index].current_state = abstd_bucket::state::occupied;
            element_size++;
            break;
        }
    }
}

size_t abstd::hash_map::get_hash_code(std::string key)
{
    size_t hash_code = 0xcbf29ce484222325;

    for(int i = 0; i < key.size(); i++)
    {
        int64_t flip;

        if((i + key[i]) % 2 == 0) flip = 0x100000001b1;
        else flip = 0x100100001b8;
        
        hash_code = hash_code ^ (flip << (key[i] & 63));
        hash_code *= 0x100000001b3;
        hash_code = (hash_code << 5) | (hash_code >> 59);
    }

    return hash_code;
}