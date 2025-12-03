# Dynamic Programming

This directory contains advanced dynamic programming techniques and optimizations.

## 📁 Subdirectories

### [optimizations/](optimizations/)
DP optimization techniques that reduce complexity:

#### Convex Hull Trick
Used when DP transitions involve linear functions and the optimal choice changes monotonically.

- **`KDLI - Convex Hull Trick 1.cpp`** - Basic CHT implementation
- **`Organizando Pacotes - Convex Hull Trick 2.cpp`** - Alternative CHT approach
- **Applications:** DP with form: dp[i] = min(dp[j] + b[j] * a[i]) where b[j] is non-increasing
- **Complexity:** O(n) with monotonic query, O(n log n) with binary search

#### Divide and Conquer Optimization
Used when DP has specific monotonicity properties.

- **`Organizando Pacotes - Divide and Counquer Optimization.cpp`** - D&C optimization for DP
- **Applications:** When cost[i][j] satisfies quadrangle inequality
- **Complexity:** Reduces O(n²k) to O(nk log n)

#### Other Optimizations
- **`Yet Another Minimization Problem.cpp`** - DP optimization techniques

**When to use:**
- **Convex Hull Trick:** When transition involves choosing best line from a set
- **D&C Optimization:** When optimal split point is monotonic with respect to i and j
- **Quadrangle Inequality:** When C[a][c] + C[b][d] ≤ C[a][d] + C[b][c] for a ≤ b ≤ c ≤ d

### [tree-dp/](tree-dp/)
Dynamic programming on trees:

- **`Karen and Supermarket.cpp`** - DP on trees with constraints
- **`MAXCHILDSUM.cpp`** - Maximum sum problems on trees

**Key concepts:**
- Root the tree and process bottom-up
- State depends on subtree information
- Use DFS to propagate states
- Common patterns: independent subtrees, paths through nodes

**Applications:**
- Tree diameter, center, radius
- Maximum independent set on trees
- Path/subtree sum problems
- Tree matching problems

### [knapsack/](knapsack/)
Knapsack variations and optimizations:

#### Sqrt Knapsack
When weights are small, use sqrt decomposition for faster DP.

- **`Lucky Country - Sqrt Knapsack.cpp`** - Basic sqrt optimization
- **`Lucky Country - Sqrt Knapsack with shift trick .cpp`** - With additional optimization
- **`PolandBall and Gifts - Sqrt Knapsack.cpp`** - Application to specific problem
- **`PolandBall and Gifts - Sqrt Knapsack with Bitset.cpp`** - Using bitsets for speed

#### Other Knapsack Problems
- **`HNUMBER.cpp`** - Specific knapsack variation

**Sqrt Knapsack Technique:**
- Group items by weight
- For small weights: standard DP
- For large weights: limited quantity, try all combinations
- **Threshold:** Usually √n or √W
- **Complexity:** O(n√n) instead of O(nW)

## 💡 Quick Reference

### Which Optimization to Use?

| Problem Type | Technique | Complexity Improvement |
|--------------|-----------|----------------------|
| Linear transitions with lines | Convex Hull Trick | O(n²) → O(n log n) or O(n) |
| Monotonic split points | D&C Optimization | O(n²k) → O(nk log n) |
| Knapsack with small weights | Sqrt Decomposition | Better constant factor |
| Tree problems | Tree DP | O(2^n) → O(n²) typically |

### Common DP Optimization Conditions

1. **Convex Hull Trick:**
   - Transition: dp[i] = min(dp[j] + cost(j, i))
   - cost(j, i) = a[i] × b[j] + c[j]
   - b[j] is monotonic

2. **Divide and Conquer:**
   - Transition: dp[i][j] = min(dp[i-1][k] + cost[k+1][j]) for k < j
   - opt[i][j] ≤ opt[i][j+1] (monotonicity)
   - Quadrangle inequality holds

3. **Sqrt Knapsack:**
   - Knapsack with weights w[i]
   - Σw[i] is small or n is small
   - Many items with same small weight
