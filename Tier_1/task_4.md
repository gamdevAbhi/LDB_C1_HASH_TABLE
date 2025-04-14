# 🧪 Task 4: Find First Non-Repeating Character

## 🧠 Problem Statement:
- Given a string**, find the first character that does not repeat. Ignore case and ignore non-alphabet characters, just
like in the anagram task.
- If no such character exists, print an appropriate message.

## ✅ Requirements & Expectations
- ✔️ Logic:
 - Ignore case (A == a)
 - Skip non-alpha characters
 - First unique character (in original order) — order matters
 - Use unordered_map<char, int> for frequency count

## ⚙️ Implementation Notes:
- Do a single-pass to build the frequency map
- Second pass to find the first character with count == 1
- Print the answer, no return needed

## 🧼 Code Quality:
- Keep functions focused (maybe a helper like clean_string() again?)
- Clean formatting
- Use std::tolower() or manual conversion for case-insensitivity