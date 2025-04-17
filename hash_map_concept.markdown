# Learn Phase: Hash Maps (LDB_C1_HASH_MAP) 📚

This document provides a comprehensive deep dive into hash maps, focusing on their internals, real-world applications, and advanced techniques. It’s designed to build a strong foundation for implementing and optimizing hash maps, especially in C++. Use this as a reference to master hash maps and enhance your programming skills.

---

## Table of Contents

1. Core Concepts
2. Internals
3. History
4. Industry Use
5. Future Trends
6. Cross-Language Differences
7. Fun Facts

---

## Core Concepts

### Hash Functions

- **Purpose**: A hash function maps a key (e.g., string, integer) to an index in the hash table’s array (e.g., `hash(key) % table_size`).

- **Properties**:

  - **Deterministic**: Same key always produces the same hash.
  - **Uniform distribution**: Spreads keys evenly across the table to minimize collisions.
  - **Fast computation**: O(1) time complexity.

- **Common Algorithms**:

  - **FNV-1a**: Popular for strings, balances speed and distribution.

    ```cpp
    uint64_t fnv1a(const std::string& s) {
        uint64_t hash = 14695981039346656037ULL;
        for (char c : s) {
            hash ^= static_cast<uint64_t>(c);
            hash *= 1099511628211ULL;
        }
        return hash;
    }
    ```

  - **MurmurHash**: Fast, used in Redis and Hadoop.

- **Pitfalls**:

  - Poor hash functions (e.g., `return key % table_size`) cause clustering, leading to O(n) performance.
  - Hash functions must handle all possible keys (e.g., empty strings, negative integers).

### Buckets

- **Definition**: The hash table’s array consists of buckets, each potentially holding one or more key-value pairs.
- **Load Factor**: Ratio of entries to table size (`n / table_size`). A load factor of 0.75 means the table is 75% full.
- **C++ Example**: `std::unordered_map` uses buckets as linked lists (chaining).

### Collision Resolution

Collisions occur when two keys hash to the same index. Two primary methods handle collisions:

- **Chaining**:

  - Each bucket holds a linked list of key-value pairs.
  - **Pros**: Simple, handles high load factors.
  - **Cons**: Memory overhead, poor cache locality due to scattered lists.
  - **C++** `unordered_map`: Uses chaining, with O(1) average and O(n) worst-case time complexity.

- **Open Addressing**:

  - All entries are stored in the array itself. When a collision occurs, probe for the next available slot.
  - **Techniques**:
    - **Linear Probing**: Check the next slot (e.g., `index + 1`).
    - **Quadratic Probing**: Use quadratic steps (e.g., `index + i^2`).
    - **Double Hashing**: Use a second hash function to determine step size.
  - **Pros**: Better cache locality, less memory overhead.
  - **Cons**: Clustering (keys bunch together), complex deletions (use tombstones).
  - **Time Complexity**: O(1) average, but degrades with high load factors.

---

## Internals

### Memory Layout

- **Chaining**:
  - Array of pointers to linked lists. Each node is dynamically allocated, leading to scattered memory and potential cache misses.
  - **C++**: `unordered_map` allocates nodes separately, impacting performance in cache-sensitive applications.
- **Open Addressing**:
  - Contiguous array of key-value pairs, improving cache hits but suffering from clustering.
  - Deletions require marking slots as “deleted” (tombstones) to avoid breaking probe sequences.

### Resizing

- **When**: Typically when the load factor exceeds a threshold (e.g., 0.75).
- **How**: Double the table size, rehash all existing entries into the new table.
- **Cost**: O(n) per resize, but amortized O(1) per operation over many inserts.
- **C++**: `unordered_map::rehash(n)` or automatic resizing on insert.

### C++-Specific Details

- **Iterator Invalidation**: Resizing invalidates all iterators in `unordered_map`, requiring careful handling in loops.

- **Custom Hash Functions**: Must define `std::hash<T>` or pass a custom hasher to `unordered_map`.

  ```cpp
  struct CustomHash {
      size_t operator()(const std::string& s) const {
          return fnv1a(s);
      }
  };
  std::unordered_map<std::string, int, CustomHash> myMap;
  ```

- **Allocators**: Customize memory allocation for performance (e.g., pooled allocators).

---

## History

- **1950s**: Hash tables first used in early compilers (e.g., IBM 701) for symbol tables.
- **1980s**: Adopted in databases like Oracle for fast lookups.
- **1990s**: STL introduced `hash_map` (later standardized as `unordered_map` in C++11).
- **2000s**: Python’s `dict` optimized for open addressing; Java’s `HashMap` added tree-based buckets for heavy collisions.

---

## Industry Use

- **Databases**:
  - **Redis**: Key-value store using hash tables for fast data retrieval.
  - **MySQL**: Hash indexes for quick lookups in tables.
- **Caching**:
  - **Memcached**: Distributed hash table for caching.
  - **Browser Caches**: URL-to-resource mappings.
- **Languages**:
  - **C++**: `unordered_map` for general key-value storage.
  - **Python**: `dict` for dictionaries and object attributes.
- **Compilers**: Symbol tables for variable and function lookups.

---

## Future Trends

- **Perfect Hashing**:
  - Generates a hash function with no collisions for static key sets. Used in compilers and databases.
  - **Example**: GNU `gperf` creates perfect hash functions for keyword lookups.
- **Cuckoo Hashing**:
  - Uses two hash functions for O(1) worst-case lookups. Common in high-performance databases.
  - **Challenge**: Detecting and resolving cycles during insertion.
- **Robin Hood Hashing**:
  - Open addressing with backward-shift deletion to balance probe lengths, reducing worst-case lookup times.
- **SIMD-Accelerated Hashing**:
  - Leverages vector instructions (e.g., SSE, AVX) to compute multiple hashes in parallel.
  - **Use Case**: Hashing batches of keys for faster processing.
- **Concurrent Hash Maps**:
  - Lock-free or fine-grained locking designs for multithreaded environments.
  - **Example**: Intel TBB’s `concurrent_hash_map`.

---

## Cross-Language Differences

- **C++** `unordered_map`:
  - **Collision Handling**: Chaining with linked lists.
  - **Features**: Custom allocators, no null keys, iterator invalidation on resize.
  - **C++20 Additions**: `erase_if` for conditional removal.
- **Python** `dict`:
  - **Collision Handling**: Open addressing with pseudo-random probing.
  - **Features**: Allows any hashable key, uses siphash for security, memory-efficient layout.
- **Java** `HashMap`:
  - **Collision Handling**: Chaining with tree fallback (since Java 8) for heavy collisions.
  - **Features**: Supports null keys, explicit load factor control, thread-unsafe by default.
- **C#** `Dictionary<TKey, TValue>`:
  - **Collision Handling**: Chaining with linked lists, similar to C++ and Java.
  - **Features**:
    - Allows null keys if `TKey` is a reference type (unlike C++).
    - Uses a combination of hashing and equality checks for lookups.
    - Not thread-safe by default; use `ConcurrentDictionary` for thread safety.
  - **Performance**: Similar to Java’s `HashMap`, with O(1) average time complexity for lookups and inserts.

---

## Fun Facts

- **Hash Flooding Attacks**: Early web frameworks (e.g., Django in 2011) were vulnerable to denial-of-service attacks by crafting inputs that caused excessive collisions, degrading performance to O(n).
- **Python’s Fix**: Python 3.3 introduced hash randomization to prevent predictable collisions.
- **MurmurHash**: A fast, non-cryptographic hash function used in Redis and Hadoop for its balance of speed and distribution.

---

## Key Takeaways for Great Programmers

- **Choose the Right Collision Resolution**: Use chaining for simplicity and high load factors; use open addressing for cache-sensitive applications.
- **Optimize Hash Functions**: Avoid clustering with well-distributed hash functions (e.g., FNV-1a, MurmurHash).
- **Handle Resizing Carefully**: In C++, be mindful of iterator invalidation after resizing.
- **Consider Security**: Use salted or randomized hashes to prevent hash flooding attacks.
- **Explore Advanced Techniques**: Techniques like cuckoo hashing or Robin Hood hashing can optimize performance for specific use cases.
- **Leverage Language Features**: Use C++17/20 features (e.g., `std::optional`, `std::string_view`) for cleaner, faster code.

---

This updated markdown file now includes C# in the **Cross-Language Differences** section, giving you a broader view of hash map implementations across languages. Save it locally for reference, and let me know if you’d like to explore any specific aspect of C#’s `Dictionary` or dive deeper into another topic! 🚀