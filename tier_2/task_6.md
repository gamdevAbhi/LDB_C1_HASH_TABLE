# Problem 1: Hash Map with Open Addressing (Linear Probing)

## Problem Description:
Implement a hash map using open addressing with linear probing to handle collisions. The hash map should support three core operations:
- put(key, value): Inserts or updates a key-value pair.
- get(key): Retrieves the value associated with the key, or indicates if the key is not found.
- remove(key): Deletes the key-value pair if it exists.
- Use a simple hash function (e.g., key modulo table size) and handle deletions properly.

## Input/Output:
- put(1, "apple") → Stores key=1, value="apple" in the hash map.
- put(9, "banana") (if 9 collides with 1, e.g., both hash to index 1 with table size 8) → Resolves collision by placing - "banana" in the next available slot via linear probing.
- get(1) → Returns "apple".
- get(2) → Returns null or an indication that the key is not found.
- remove(9) → Marks the slot as deleted; subsequent get(9) returns null/not found.

## Expectations:
- Implement in C++ using a fixed-size array as the underlying storage.
- Use linear probing for collision resolution (i.e., check index + 1, index + 2, etc., wrapping around if needed).
- Handle deletions using tombstones to preserve probe sequences (as covered in Micro-Quiz 8, April 16, 2025).
- Test edge cases, including:
- Full table (no available slots).
- High collision rates (multiple keys hashing to the same index).
- Empty keys or invalid inputs (if applicable).