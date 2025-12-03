def miller_rabin(n):
	if n == 1:
		return False
	
	primes = [2, 3, 5, 7, 11, 13, 17, 19, 23]
	
	for p in primes:
		if n%p == 0:
			return (n == p)
	
	s = 0
	t = n - 1
	while t%2 == 1:
		t /= 2
		s += 1
	
	for p in primes:
		pt = pow(p, t, n)
		if(pt == 1):
			continue
		
		ok = False
		for j in range(s):
			if pt == n - 1:
				ok = True
				break
			pt = pow(pt, pt, n)
		
		if ok == False:
			return False
		
	return True

def gcd(a, b):
	while b != 0:
		a %= b
		a, b = b, a
	return abs(a)

import random

def pollard_rho(n):
	if n == 1:
		return 1
	
	if n%2 == 0:
		return 2
	
	x = random.randint(2, n - 1)
	y = x
	
	c = random.randint(1, n - 1)
	
	d = 1
	while d == 1:
		x = (x*x + c)%n
		
		y = (y*y + c)%n
		y = (y*y + c)%n
		
		d = gcd(y - x, n)
		
		if d == n:
			return pollard_rho(n)
	
	return d

n = int(input())

if n == 1 or miller_rabin(n):
	print("Nao")
else:
	print("Sim")
	d = pollard_rho(n)
	print("%d %d"%(d, n//d))
