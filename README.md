# 🔧 LDB_C1_Hash_Table

A low-level implementation of a hash table as part of my **LDB (Learn-Do-Build)** personal development series.  
This repo focuses purely on the **Learn** and **Doing** phase — deep diving into how hash tables work under the hood and implementing them from scratch using C++.

---

## 🚀 Goal

- Understand the internals of hash tables.
- Explore different collision handling techniques (linear probing, chaining, etc.).
- Implement a basic hash table from scratch in C++.
- Focus on memory layout, performance, and correctness.
- Learn about perfect hashing, cuckoo hashing, robin hood hashing, SIMD hashing

---

# 🔍 Hash Table Learning, Doing, Building Cycle

> Language Focus: **C++**  
> Goal: Master hash tables through progressive practice, deep dives, and system-building.

---

## ✅ Tier 1: STL-Based Practice (C++ `unordered_map`)

| Task                                                | Status |
|-----------------------------------------------------|--------|
| Basic CRUD with `unordered_map`                     | ✅     |
| Count frequency of characters in a string           | ✅     |
| Check if two strings are anagrams                   | ✅     |
| First non-repeating character                       | ✅     |
| Group anagrams from a list of words                 | ✅     |

---

## ⚙️ Tier 2: Build, Compare, Extend

| Task | Status |
|------|--------|
| Build your own Hash Map from scratch (Open Addressing + Linear Probing) | ✅ |
| Build your own hash set (Chaining) | ✅ |
| Benchmark linear probing vs. chaining | skip |

---

## 🔬 Tier 3: Advanced Topics & Real-World Exploration

| Task | Status |
|------|--------|
| Implement Robin Hood hashing | ✅ |
| Implement Cuckoo hashing | ✅ |
| Hash Flood mitigation | 🔜 |
| Implement Perfect hashing | 🔜 |
| Experiment with SIMD hashing | 🔜 |

---

## 🔨 Build Phase

**Goal**: Create a reusable hash table library with multiple implementations (linear probing, chaining, Robin Hood, Cuckoo).

**Deliverable**: A C++ header-only library (`abstd::hash_table`) with configurable collision strategies, generic key-value support, and benchmarks.

**Features**:

- Template-based generic hash map and set
- Switchable collision handling (e.g., via policy classes)
- Performance metrics (collisions, probe lengths, cache misses)
- Utilities like iteration and serialization

**Example Use Case**: Build a word frequency counter with multiple hash table backends to compare performance.

---

## 🔄 Workflow Reminder

- 🔹 **Learn Phase:** Research concepts deeply
- 🔹 **Do Phase:** Solve problems, write utilities
- 🔹 **Build Phase:** Create full-featured systems or toolsets
- 🧠 Language Focus: C++

## 🧠 Learning Notes

- As I am learning things.. codes might contains bugs and issues. this are not production ready code.
> Every commit is part of the learning log — expect code experiments, cleanup, and iterations.
> Final production-grade version (if any) will be moved to a separate repo in the `Build` phase.

---
