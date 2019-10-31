# AC 1.63s 27M py3.5 SPOJ
# 
# stjepan algorithm (https://apps.topcoder.com/forums/%3bjsessionid=3287ACECF9CF17908ABE58184A360228?module=Thread&threadID=666160&start=0&mc=10#1222646)
# 
# If a/b < 1 and c/d > 1 the answer is p = q = 1.
# If floor(a/b)+1 < c/d, the answer is p = floor(a/b)+1, q = 1.
# If a < b, transform the inequalities like this: d/c < q/p < b/a.
# 
# Otherwise, we need this reduction:
# a/b < p/q < c/d
# a/b - 1 < p/q - 1 < c/d - 1
# (a-b)/b < (p-q)/q < (c-d)/d
# 
# Or, to speed things up, let k = floor(a/b)
# a/b < p/q < c/d
# a/b - k < p/q - k < c/d - k
# (a-kb)/b < (p-kq)/q < (c-kd)/d
# 
# when a == 0, obviously when it is transformed to d/c < q/p < b/a, 
# but is will be handled in floor(a/b)+1 < c/d case, because, we assume that x/0 == infinity.
# 
# I'm still not sure about d/c < q/p < b/a case, when it is backflipped, it searches for smallest p, then smallest q.
# but the problem asked for smallest q first, then smallest p.
#
# space O(log(N))
# time O(log(N))

import os
import sys

def gcd(a,b):
	if b == 0:
		return a
	else:
		return gcd(b, a%b)

def F(a,b,c,d):
	if (a<b) and (c>d):
		return (1,1)
		
	# actually handles the case if d == 0 from a == 0
	
	k = a//b
	if (a+b)*d < b*c:
		return (k + 1, 1)
	
	if a >= b:
		(pr, qr) = F(a - k*b, b, c - k*d, d)
		return (pr + k*qr, qr)
		
	else:
		(pr, qr) = F(d, c, b, a)
		return (qr, pr)
		

def main():
	for rlin in sys.stdin:
		var = [int(x) for x in rlin.strip().split(' ')]
		(p,q) = F(var[0], var[1], var[2], var[3])
		print("%d/%d" % (p,q))

if __name__ == "__main__":
	main()