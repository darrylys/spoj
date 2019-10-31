# AC, 0.72 s.
# concerns on sqrt accuracy but still AC.

# algorithm
# given N days, protagonist can kill a maximum of:
# if N=2n+1, he can kill (n+1)^2. Structure: 1 2 3 ... n (n+1) n (n-1) ... 2 1
# else, he can kill n*(n+1). Structure: 1 2 3 ... n n (n-1) ... 2 1
# from this maximum configuration, we can always reduce 1 to accomodate smaller values and still following the requirement
# so, there are 2 cases possible
# n = sqrt(N) - 1 for odd possible days, or n = (sqrt(1 + 4N)-1)/2 (from standard quadratic solution) for even possible days
# find the ceil of each and compare the minimum. for odd, 2n+1 and for even, 2n.

from math import sqrt
from math import ceil
import sys

sys.stdin.readline()

for line in sys.stdin:
	A = int(line)
	
	cen = ceil((sqrt(1+4*A)-1)/2)
	con = ceil(sqrt(A)-1)
	
	print("%d" % (min(cen*2, con*2+1)))
	
	
