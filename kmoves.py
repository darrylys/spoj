# AC 0.13s 23M SPOJ PYTHON3
# 
# Algo: math
# 
# this is a very cool problem
# To solve this problem, try to bruteforce manually by hand using excel
# It can be seen that when the number of steps = 3 and above, the blocks that can be visited
# exactly n steps is a completely filled octagon with (n+1)-length sides.
# 
# Only exception is when steps = 2. There are 4 places that cannot be visited within the octagon
# 
# To prove this, math induction can be used.
# Lets assume that octagon for (n-1) and (n) steps are all completely filled
# we want to prove that the (n+1) steps are also completely filled
#
# The (n+1) octagon can be divided to two sections. The inner part and the outer part.
# The inner part is actually the (n-1)-length octagon. This can be reconstructed from (n)-length octagon with 
# adding the last step to simply redo the last step when (n)-length octagon is constructed from (n-1) one.
# Thus, the inner part is completely filled.
# 
# The outer part will be the inner part added with 3 outer layers. @see book1.xlsx for more details
# These 3 layers can be constructed easily and are completely filled as well.
# Outermost layer can be constructed by simply doing one step from (n) length octagons' outermost squares.
# Similarly with the middle and lower layer.
# 
# Therefore, the (n+1)-length octagon is also filled completely.
# 
# Space: O(1)
# Time: O(T)

import os
import sys

def main():
	sys.stdin.readline()
	
	for rline in sys.stdin:
		n = int(rline.strip())
		if n%2 == 1:
			print("0")
		elif n == 0:
			print("1")
		elif n == 2:
			print("33")
		else:
			print("%d" % ( n*(3*n+1) + (n+1)*(2*n+1) + n*(2*n) ))
	
if __name__ == '__main__':
	main()
