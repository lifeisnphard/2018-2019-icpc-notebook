# String Algorithms

This directory contains implementations of string processing and pattern matching algorithms.

## 📄 Implementations

### Pattern Matching
- **`KMP.cpp`** - Knuth-Morris-Pratt algorithm for pattern matching in O(n+m) time
- **`Z Algorithm.cpp`** - Z-array for finding all occurrences of pattern in text

### Substring Problems
- **`Distinct Substrings - Easy to code O(n^2).cpp`** - Simple O(n²) solution for counting distinct substrings
- **`Distinct Substrings - Hashing.cpp`** - Using polynomial hashing for distinct substring counting
- **`Distinct Substrings - Suffix Array O(N log^2(N)).cpp`** - Suffix array approach for distinct substrings

## 💡 When to Use

### KMP Algorithm
- Finding pattern occurrences in text
- Prefix function computations
- String matching with wildcards
- **Complexity:** O(n + m) where n is text length, m is pattern length

### Z Algorithm
- Finding all occurrences of pattern in text
- Comparing suffixes efficiently
- String matching problems
- **Complexity:** O(n + m)

### Hashing
- Quick substring comparison
- Multiple pattern matching
- When exact matching is not critical (collision probability exists)
- **Complexity:** O(n) preprocessing, O(1) per query

### Suffix Array
- Finding distinct substrings
- Longest common prefix (LCP) problems
- Multiple pattern searches
- **Complexity:** O(n log² n) for construction

## 🔍 Algorithm Comparison

| Algorithm | Preprocessing | Query | Use Case |
|-----------|--------------|-------|----------|
| KMP | O(m) | O(n) | Single pattern matching |
| Z Algorithm | O(n+m) | - | Pattern occurrences |
| Hashing | O(n) | O(1) | Fast substring comparison |
| Suffix Array | O(n log² n) | O(m log n) | Multiple patterns, LCP |

## 📚 Common Problems

- **Pattern Matching:** Use KMP or Z Algorithm
- **Distinct Substrings:** Use Suffix Array or Hashing
- **Palindrome Detection:** Can use KMP with reversed string
- **Longest Common Substring:** Suffix Array with LCP
- **Multiple Pattern Matching:** Aho-Corasick (not yet implemented) or Suffix Array
