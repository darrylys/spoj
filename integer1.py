# AC 0.02s 28M SPOJ
#
# algo: math
# difficulty: floating point arithmetic is innacurrate. Some caution should be done
# 
# Problem: 
# For a given positive integer y(y > 1), if we can find a largest integer k and a smallest positive integer x, such that x^k=y, then the power of y is regarded as k.
# Calculate the sum of the power of the integers from a to b. (2<= a <= b <=10^18)
#
# Solution:
# k is always in [1,64] because 2^64 > 10^18
# from this, we can simply enumerate all possible k and find out how many of them actually are
# 
# how many of 64, 63, ..., 10, 9, 8, ..., 2, 1
# and sum all of them
# 
# basically, foreach k in (64, 63, ..., 2)
# the numbers from n in (2, 3, ... floor(N, 1/k)), satisfies the following:
#               n ^ k <= N
#
# However, if n satisfies the equation m^o = n for m < n and o > 1, n must be excluded because it has been counted previously in higher k. 
# if n = m^o, then, n^k = m^ok. ok > k because o > 1 and therefore has been calculated previously.
# 
# so, exclude all counts from
#    o * k | o > 1.
# 
# 
# Space: O(lg(N))
# Time: O(lg(N)lg(lg(N)))
# 

import os
import sys
import math

def findv(N):
	#print(">> findv(%d)" % N)
	
	top = int(math.floor(math.log2(N)))
	while (1<<(top+1)) <= N:
		top += 1
	
	while (1<<(top)) > N:
		top -= 1
	
	arr = [0]*(top+2)
	
	#print("top=%d" % top)
	
	sumarr = 0
	sumexp = 0
	
	si = top
	while si > 1:
		#print("\tsi=%d" % si)
		
		# problem here!!
		# N = floor((10^15-1)^(1/5)) should be 999
		# but in this case, the result by python 3 is actually 1000!
		lim = int(math.floor(math.pow(N, (1/si))))
		
		# make accurate
		while ((lim+1)**si) <= N:
			lim += 1
		
		while ((lim)**si) > N:
			lim -= 1
		
		#print("\tlim=%d, lim**si=%d, (lim+1)**si=%d, N=%d" % (lim, lim**si, (lim+1)**si, N))
		
		diff = lim-1
		i=2*si
		while i <= top:
			diff -= arr[i]
			i += si
			
		
		#print("\tdiff=%d" % diff)
		
		arr[si] = diff
		sumarr += diff
		sumexp += diff * si
		
		#print("================")
		
		si -= 1
	
	sumexp += N - sumarr
	
	return sumexp
	

def main():
	for rline in sys.stdin:
		arr = rline.strip().split(' ')
		a = int(arr[0])
		b = int(arr[1])
		
		if a == 0 and b == 0:
			break
		
		print("%d" % (findv(b) - findv(a-1)))
		

	
if __name__ == "__main__":
	main()
	