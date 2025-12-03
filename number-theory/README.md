# Number Theory

This directory contains implementations of number-theoretic algorithms and functions.

## 📄 Implementations

### Euler's Totient Function (Phi)
Counts numbers less than n that are coprime to n.

- **`ETF - Phi O(N log(N)) pre-processing.cpp`** - Sieve-based preprocessing for multiple queries
- **`ETF - Phi O(N) pre-processing.cpp`** - Linear time sieve
- **`ETF - Phi by Factorization.cpp`** - Compute phi(n) by prime factorization
- **`GCDEX - Phi.cpp`** - Using phi for GCD sum problems

### Möbius Function
Used in inclusion-exclusion and divisor-related problems.

- **`GCDEX - Mobius.cpp`** - GCD sum using Möbius function
- **`Coprime Arrays - Mobius.cpp`** - Count coprime arrays
- **`Mike and Foam - Bitmask + Mobius.cpp`** - Inclusion-exclusion with bitmask
- **`Mike and Foam - Linear Sieve + Mobius.cpp`** - Linear sieve for Möbius
- **`Unusual Sequences - Mobius.cpp`** - Sequence counting with Möbius

### Modular Arithmetic
- **`CRT from Codeforces.cpp`** - Chinese Remainder Theorem implementation
- **`Cifra Affline - Modular Inverse by Diophantine Equations.cpp`** - Extended GCD for modular inverse

### Coprimality and GCD
- **`Coprime Arrays - DP.cpp`** - Dynamic programming approach for coprime arrays
- **`Coprime Triples.cpp`** - Finding coprime triplets
- **`Unusual Sequences - Backtrack.cpp`** - Backtracking approach for sequence problems

## 💡 When to Use

### Euler's Totient Function (φ)
- Counting numbers coprime to n
- Euler's theorem: a^φ(n) ≡ 1 (mod n) when gcd(a,n) = 1
- Sum of GCD problems
- Counting primitive roots
- **Formula:** φ(n) = n × ∏(1 - 1/p) for all prime divisors p

### Möbius Function (μ)
- Inclusion-exclusion principle
- Inversion formulas: f(n) = Σd|n g(d) ⟺ g(n) = Σd|n μ(d)f(n/d)
- Counting coprime pairs
- Divisor sum transformations
- **Values:** μ(n) = 1 if n is square-free with even prime factors, -1 if odd, 0 if not square-free

### Chinese Remainder Theorem (CRT)
- Solving system of modular equations
- Combining results from different moduli
- When working with coprime moduli
- **Condition:** Moduli must be pairwise coprime

### Modular Inverse
- Division in modular arithmetic
- Computing binomial coefficients modulo prime
- Solving linear congruences
- **Methods:** Extended GCD, Fermat's Little Theorem

## 📊 Complexity Comparison

| Algorithm | Time Complexity | Use Case |
|-----------|----------------|----------|
| Phi by factorization | O(√n) | Single query |
| Phi sieve (O(n log n)) | O(n log n) | Multiple queries ≤ n |
| Phi linear sieve | O(n) | Multiple queries ≤ n |
| Möbius linear sieve | O(n) | Multiple queries ≤ n |
| CRT | O(k log m) | k equations, m = max modulus |
| Modular inverse (ExtGCD) | O(log n) | Single computation |

## 🔢 Common Formulas

- **φ(p^k) = p^k - p^(k-1)** for prime p
- **φ(mn) = φ(m)φ(n)** when gcd(m,n) = 1
- **Σd|n φ(d) = n**
- **μ(mn) = μ(m)μ(n)** when gcd(m,n) = 1
- **Σd|n μ(d) = [n=1]** (1 if n=1, 0 otherwise)
