# ICPC/IOI Competitive Programming Notebook (2018-2019)

This is an ACM ICPC code notebook compiled in 2018. The codes here were written in the period of 2014 - 2018. Most of them were written when I was still in High School, so they may not contain the most elegant solution.

## 📚 Repository Structure

This repository is organized by algorithm category and data structure type to facilitate quick reference during competitions:

### 🌳 Data Structures
- **[trees/](data-structures/trees/)** - Segment Trees, BIT (Fenwick Trees), Treaps, Persistent Structures, Implicit Trees, Merge-Sort Trees
- **[advanced/](data-structures/advanced/)** - Sqrt Decomposition, Mo's Algorithm, Disjoint Set Operations
- **[ordered-sets/](data-structures/ordered-sets/)** - Policy-based data structures for ordered operations

### 📊 Graph Algorithms
- **[trees/](graph-algorithms/trees/)** - LCA (Lowest Common Ancestor), HLD (Heavy-Light Decomposition), Centroid Decomposition, DSU on Trees
- **[mst/](graph-algorithms/mst/)** - Minimum Spanning Tree algorithms and variations
- **[shortest-paths/](graph-algorithms/shortest-paths/)** - Dijkstra, Bellman-Ford, Floyd-Warshall, negative cycle detection
- **[other/](graph-algorithms/other/)** - DAG operations, graph queries, and miscellaneous graph problems

### 🔤 String Algorithms
- **[string-algorithms/](string-algorithms/)** - KMP, Z Algorithm, Suffix Arrays, Hashing, Pattern Matching

### 🔢 Number Theory
- **[number-theory/](number-theory/)** - GCD/LCM, Modular Arithmetic, CRT (Chinese Remainder Theorem), Euler's Totient (Phi), Möbius Function, Prime Factorization

### 🎯 Dynamic Programming
- **[optimizations/](dynamic-programming/optimizations/)** - Convex Hull Trick, Divide and Conquer Optimization
- **[tree-dp/](dynamic-programming/tree-dp/)** - Dynamic Programming on Trees
- **[knapsack/](dynamic-programming/knapsack/)** - Knapsack variations and optimizations

### 📐 Geometry
- **[geometry/](geometry/)** - Currently empty, basic geometric templates available in templates/

### 📋 Templates
- **[templates/](templates/)** - Basic code templates for Geometry, Number Theory, and common utilities

### 🎓 Problems
- **[problems/](problems/)** - Complete problem solutions from various competitions (ICPC, IOI, Codeforces, SPOJ, etc.)

## 🚀 Usage

### For Competitions
1. Navigate to the appropriate category directory
2. Find the algorithm or technique you need
3. Copy the implementation to your solution

### Building the Notebook PDF
Use the provided `caderno.sh` script to generate LaTeX sections for creating a printable notebook (requires updating for new structure).

## 📖 Quick Reference

### Most Common Techniques by Category:

**Data Structures:**
- Binary Indexed Tree (BIT/Fenwick Tree)
- Segment Tree (with lazy propagation)
- Treaps (Implicit and Explicit)
- Persistent Segment Tree

**Graph Algorithms:**
- Heavy-Light Decomposition (HLD)
- Lowest Common Ancestor (LCA)
- Centroid Decomposition
- DSU (Disjoint Set Union) / Union-Find

**Number Theory:**
- Euler's Totient Function
- Möbius Function
- Modular Arithmetic
- Chinese Remainder Theorem

**DP Optimizations:**
- Convex Hull Trick
- Divide and Conquer Optimization
- Knapsack with Sqrt Decomposition

## ⚠️ Note

These implementations were created for competitive programming and prioritize speed of implementation over code elegance. They have been tested on various online judges but may not follow best software engineering practices.
