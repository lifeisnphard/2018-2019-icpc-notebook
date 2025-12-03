# Data Structures

This directory contains implementations of various data structures commonly used in competitive programming.

## 📁 Subdirectories

### [trees/](trees/)
Advanced tree-based data structures:
- **Segment Trees** - Range query and update structures with lazy propagation
- **Binary Indexed Tree (BIT/Fenwick Tree)** - Efficient prefix sum queries
- **Treaps** - Randomized binary search trees (both explicit and implicit)
- **Persistent Segment Trees** - Version control for segment trees
- **Merge-Sort Trees** - Find k-th element in range queries
- **2D Segment Trees** - Two-dimensional range queries

**Key implementations:**
- `ORDERSET - BIT.cpp` - Order statistics with BIT
- `ORDERSET - Treap.cpp` - Order statistics with Treap
- `Fila - Implicit Treap.cpp` - Queue operations using implicit treap
- `MKTHNUMBER - Persistent SegTree.cpp` - K-th number queries with persistence
- `Game - (Implicit SegTree 2D).cpp` - 2D range operations

### [advanced/](advanced/)
Advanced data structures and techniques:
- **Sqrt Decomposition** - Break array into √n blocks for faster queries
- **Mo's Algorithm** - Offline query processing technique
- **Disjoint Set Operations** - Set-based range operations

**Key implementations:**
- `Mass Change Queries - SQRT Decomposition + list splice.cpp` - Efficient mass updates
- `One Occurrence - Mo + Sqrt Decomposition.cpp` - Find unique elements in ranges
- `Daunting Device - Lazy on Sqrt Decomposition.cpp` - Lazy propagation on blocks

### [ordered-sets/](ordered-sets/)
Policy-based data structures from GNU C++ extensions:
- Order statistics trees
- Rank queries in O(log n)

**Key implementation:**
- `Ordenando Árvores - Ordered Set.cpp` - Using GNU pbds ordered set

## 💡 When to Use

- **Segment Tree** - When you need range queries and updates with custom operations
- **BIT** - When you only need prefix operations (sum, XOR, etc.)
- **Treap** - When you need a balanced BST with split/merge operations
- **Persistent Structures** - When you need to access previous versions of data
- **Sqrt Decomposition** - When segment tree is too complex or you need simple block operations
- **Mo's Algorithm** - For offline queries when direct computation is expensive
