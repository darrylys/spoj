#  
# AC 0.02s 9.8M SPOJ
# 
# python 3.4
# 
# algo: math
# 
# First, lets model this problem
# The problem asks to find a number X which the last digits of X^3 is given at input.
#
# In modular equation:
# find X where (X^3) mod 10^(number of digits of n) == [given n digit number]
# 
# We are given guarantee that X is definitely exist.
# 
# Now, consider the following
# X = 10^(n-1)X_1 + 10^(n-2)X_2 + ... + 10X_(n-1) + X_n
# where X_n is [0,9]
# 
# So, we need to solve this polynomial instead:
# (10^(n-1)X_1 + 10^(n-2)X_2 + ... + 10X_(n-1) + X_n)^3 mod 10^(number of digits of N) == N                                  (1)
# 
# now, first, lets find the last digit of X.
# we can see that if X ended with 1 or 9, X^3 will end up with 1 or 9 as well.
# and if X ended with 3, X^3 ended with 7 and vice versa.
#
# So, the last digit of X can be easily determined.
#
# How about the next digits?
# Notice that nth digit of X is only determined by digits (n+1) and above.
# so, to find nth digit, the mod part in equation (1) can be changed to 10^n.
# 
# start from the first digit, we can work out the rest of the digits.
# 
# step 1:
# equation starts with: 
# (10^(n-1)X_1 + 10^(n-2)X_2 + ... + 100X_(n-2) + 10X_(n-1) + X_n)^3 mod 100 == N%100
# Notice that all terms before X_(n-1) are all become zeros because of the mod 100.
# plug in X_n = last digit of X. 
# 
# The equation above becomes:
# (10X_(n-1) + X_n)^3 mod 100 == N%100
# (10a + b)^3 mod 100 == N%100
# Now, this is MUCH easier to work with.
# 
# expand above equation and remove all terms which will be zeros if modded by 100
# Most of the terms will be gone
# (1000 a^3 + 300 a^2 b + 30 a b^2 + b^3) mod 100 == N%100
# (30 a b^2 + b^3) mod 100 == N%100
# 
# so, a will be:
# a = (30 * b^2)^(-1) * (N%100 - b^3) mod 100
# 
# Notice that since N%100 and b^3 will differ only at the first digit, (N%100 - b^3) is divisible by 10.
# also remember that 30 * b^2 is also divisible by 10.
# Notice also that gcd(b, 100) is always 1. This shows that the invert mod will always exist.
# the equation will be like:
# 10kA == 10B mod 100.
# 
# The above observation allow us to divide this whole thing by 10 resulting:
# kA == B mod 10
# with gcd (k, 10) = 1
#
# plugin this value to X_(n-1) and continue the process.
# Note that only one possible X_(n-1) exist within [0,9]. This proves that only one X can exist within [0, 10^n).
# 
# step 2:
# solve the equation using the same method:
# b = 10*X_(n-1) + X_n
# (100a + b)^3 mod 1000 == N%1000
# X_(n-2) = a
#
# and so on...
#
# Time: O(number of digits of N)
# Space: O(constant)

import os
import sys

def egcd(a, b):
	if a == 0:
		return (b, 0, 1)
	else:
		g, y, x = egcd(b % a, a)
		return (g, x - (b // a) * y, y)

def modinv(a, m):
	g, x, y = egcd(a, m)
	if g != 1:
		raise Exception('modular inverse does not exist')
	else:
		return x % m

def findX3(N, dl):
	
	#print(">> findX3(%d,%d)" % (N, dl))
	
	X = 0
	# first digit
	if (N%10 == 1 or N%10 == 9):
		X = N%10
	elif (N%10 == 7):
		X = 3
	else:
		X = 7
	
	tm = 100
	tx = 10
	tl = 10**dl
	X1 = 0
	
	# find other digits
	while (tm <= tl):
		
		# equation:
		# (tx * X1 + X)^3 % tm == N % tm
		# we need to find X1
		
		ntx = tx
		nx = X
		
		#print("eq= (%d X1 + %d) mod %d == %d" % (ntx, nx, tm, N%tm))
		
		# obtain (tx * X1 + X)^2
		ntx = (ntx * X + nx * tx)%tm
		nx = (nx * X)%tm
		
		# obtain (tx * X1 + X)^3
		ntx = (ntx * X + nx * tx)%tm
		nx = (nx * X)%tm
		
		# equation becomes: (ntx X1 + nx)%tm == N%tm
		nX = (N%tm)-nx
		if nX < 0:
			nX += tm
			
		
		#print("eeq^3 = (%d X1 + %d) mod %d == %d" % (ntx, nx, tm, N%tm))
		
		ntx = ntx // tx
		nX = nX // tx
		
		dinv = modinv(ntx, 10)
		
		#print("dinv = %d" % dinv)
		
		X1 = (dinv * nX)%10
		
		X += X1*tx
		tx *= 10
		tm *= 10
	
	#print("<< findX3(): %d" % X)
	
	return X

def main():
	sys.stdin.readline()
	
	for rawline in sys.stdin:
		
		rline = rawline.strip()
		dl = len(rline)
		num = int(rline)
		
		print(findX3(num, dl))
	
if __name__ == '__main__':
	main()

