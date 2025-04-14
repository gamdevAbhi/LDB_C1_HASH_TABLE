# 🧩 Task 3: Anagram Checker

## 🧠 Problem Statement:
- Write a function that takes two strings and returns whether they are anagrams of each other.
- Ignore: 
 - Case (e.g., A == a)
 - Whitespace and punctuation

## ✅ What I Expect From Your Code:
 - ✔️ Functional:
  - Use a hash table (unordered_map<char, int>) to count character frequencies.
  - Compare the two frequency maps for equality.
  - Treat upper/lowercase as same (tolower or manual).
  - Ignore all non-alphabetic characters (isalpha or manual check).

 - 🧼 Structure & Style:
  - One main function, maybe with helper like clean_string() or count_characters().
  - No duplicated logic — if you're cleaning both strings, extract that logic.

 - 🧠 Optimization:
  - One-pass counting is fine.
  - Don't sort or use unnecessary data structures.