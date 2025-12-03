# Templates

This directory contains basic code templates and utility implementations that can be used as starting points for solutions.

## 📄 Implementations

### Geometry Template
**`Geometry Basic Template.cpp`**

Provides basic geometric operations and structures:

**Features:**
- `struct point` - 2D point with operator overloading
- Vector operations: addition, subtraction, scalar multiplication/division
- Dot product (`*`) and cross product (`|`)
- Distance and norm calculations
- Point rotation
- Perpendicular vector

**Common operations:**
```cpp
point a, b;
ld distance = (b - a).abs();           // Distance between points
ld dot = a * b;                        // Dot product
ld cross = a | b;                      // Cross product
point rotated = a.rotate(angle);       // Rotate by angle
point perp = a.perp();                 // Perpendicular vector
```

**When to use:**
- Computational geometry problems
- Point and vector operations
- Line and segment problems
- Polygon operations
- Convex hull

### Number Theory Template
**`Number Theory Basic Template.cpp`**

Provides essential number theory functions:

**Features:**
- GCD (Greatest Common Divisor)
- LCM (Least Common Multiple)
- Extended GCD
- Diophantine equations solver
- Modular inverse
- Modular exponentiation
- Ordered set from GNU PBDS

**Common functions:**
```cpp
ll gcd(ll a, ll b);                    // GCD
ll lcm(ll a, ll b);                    // LCM
ll ext_gcd(ll a, ll b, ll &x, ll &y); // Extended GCD
ll diophantine(ll a, ll b, ll c, ll &x, ll &y); // Solve ax + by = c
ll get_inv(ll a, ll m);                // Modular inverse
ll modpow(ll a, ll x, ll m);          // a^x mod m
```

**When to use:**
- Modular arithmetic problems
- Prime numbers and factorization
- Linear Diophantine equations
- Computing combinations modulo prime
- Cryptography problems

## 🔧 Utility Features

### Data Types
Both templates include:
```cpp
using ll = long long;
using llu = unsigned long long;
using ld = long double;
```

### Common Macros
```cpp
#define len(x) ((int)(x).size())
#define x first
#define y second
```

### Ordered Set (Number Theory Template)
```cpp
template<typename T> using ordered_set = tree<...>;
```
- Insert, erase, find in O(log n)
- Find k-th element: `find_by_order(k)`
- Count elements less than x: `order_of_key(x)`

### Comparison with Epsilon (Number Theory Template)
```cpp
inline int cmp(ld x, ld y = 0, ld tol = EPS);
```
- Returns: -1 if x < y, 0 if x ≈ y, 1 if x > y
- Handles floating point comparisons safely

## 💡 Usage Tips

### Starting a New Problem

1. **Geometry problem:**
   - Copy `Geometry Basic Template.cpp`
   - Add specific geometry algorithms as needed
   - Use the point struct for all coordinate operations

2. **Number theory problem:**
   - Copy `Number Theory Basic Template.cpp`
   - Use provided GCD, modular arithmetic functions
   - Extend with problem-specific number theory

3. **General problem:**
   - Take macros and type definitions
   - Add specific data structures from other directories
   - Keep only what you need for the problem

### Customization

- **Modify MOD:** Change `const int MOD = 1;` to your required modulus
- **Adjust EPS:** Change `const ld EPS = 1e-9;` for different precision
- **Add includes:** Both templates use `#include <bits/stdc++.h>` for convenience

### Best Practices

- Test template functions before competition
- Understand each function's complexity
- Know when to use extended GCD vs Fermat's theorem for modular inverse
- For geometry, be careful with floating point precision
- Use ordered_set when you need both BST operations and order statistics
