# AC, 0.01s, SPOJ, 9.1M.
# algo: v -> binary -> find all 3**x where xth bit of v is 1.
# try to imagine instead of 3**x, we have 2**x. All subset of 2**x is ordered by sum of the members
# the sum sequence will be the sequence of all natural numbers with the contents of subset is the sum represented in binary form.
# it is exactly the same as in 3**x, just bigger.

import os
import re
import sys

a3 = [str(3**x) for x in range(0, 65)]

for line in sys.stdin:
	v = int(line)
	if v == 0:
		break
	
	if v == 1:
		print("{ }")
		continue
	
	v -= 1
	
	j = [a3[x] for x in range(0, 65) if (v & (1<<x) != 0)]
	print("{ %s }" % ", ".join(j))
	
