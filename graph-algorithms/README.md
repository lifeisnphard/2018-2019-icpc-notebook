# Graph Algorithms

This directory contains implementations of various graph algorithms for competitive programming.

## 📁 Subdirectories

### [trees/](trees/)
Advanced tree algorithms and queries:
- **LCA (Lowest Common Ancestor)** - Find common ancestor of two nodes
- **HLD (Heavy-Light Decomposition)** - Convert tree paths to array segments
- **Centroid Decomposition** - Divide and conquer on trees
- **DSU on Trees** - Small-to-large merging technique
- **Tree Queries** - Various query problems on trees

**Key implementations:**
- `QTREE.cpp`, `QTREE2.cpp`, `QTREE5.cpp` - Classic SPOJ tree query problems
- `COT.cpp`, `COT2.cpp` - Count on Tree problems
- `Linhas de Metro - HLD.cpp` - Heavy-Light Decomposition
- `Jogo da Memória - Offline Tarjan LCA.cpp` - Offline LCA with Tarjan's algorithm
- `Race - Centroid Decomposition.cpp` - Path queries with centroid decomposition
- `Race - DSU on Trees.cpp` - Small-to-large merging on trees
- `Xenia and Tree - Centroid Decomposition.cpp` - Distance queries

### [mst/](mst/)
Minimum Spanning Tree algorithms and variations:
- **Kruskal's Algorithm** - MST with Union-Find
- **MST with additional constraints** - LCA on MST for path queries

**Key implementations:**
- `Caminhão - MST + LCA.cpp` - MST combined with LCA
- `Caminhão - Offline queries with Union-Find.cpp` - Offline query processing
- `Xor-MST.cpp` - MST with XOR weights

### [shortest-paths/](shortest-paths/)
Shortest path algorithms:
- **Dijkstra's Algorithm** - Single-source shortest paths (non-negative weights)
- **Bellman-Ford** - Single-source with negative weights
- **Floyd-Warshall** - All-pairs shortest paths
- **Negative Cycle Detection** - Finding negative cycles

**Key implementations:**
- `Quase menor caminho.cpp` - Almost shortest path problem
- `Perpetuum Mobile - Negative Cycle with Floyd Warshall.cpp` - Detect negative cycles

### [other/](other/)
Miscellaneous graph algorithms:
- **DAG operations** - Directed Acyclic Graph algorithms
- **Graph queries** - Various types of graph query problems
- **Dynamic connectivity** - Handle edge additions/deletions

**Key implementations:**
- `Chef and Graph Queries.cpp` - Dynamic graph queries
- `DAGCNT.cpp` - Counting on DAGs
- `DRTREE.cpp` - Tree-related operations

## 💡 When to Use

- **LCA** - Finding common ancestors, distance between nodes
- **HLD** - Path queries/updates on trees that need fast segment tree operations
- **Centroid Decomposition** - Distance-based problems on trees, path counting
- **DSU on Trees** - Subtree queries, frequency problems
- **Kruskal/Prim** - Finding minimum spanning trees
- **Dijkstra** - Shortest path with non-negative weights
- **Bellman-Ford** - Shortest path with negative weights, cycle detection
- **Floyd-Warshall** - All-pairs shortest paths, transitive closure
