# AC, 0.04 SPOJ, 9.6M just for shit and giggles, I used python

# Lets create a model using graph
# each cell is one node.
#
# the act of coloring means adding a directed edge to the neighboring cells 
# to the cells that has been colored.
# the score will be the number of directed edge added.
# 
# basically, the number of directed edge added will be the same
# no matter in what order the cells are colored.
#
# so, just pick a simple ordering:
# sample:
# 0	1	1
# 1	2	2
# 1	2	2
# 1	2	2
# 1	2	2
# 1	2	2
#
# and the formula can be easily constructed.

import os
import sys

T = int(sys.stdin.readline())
t=0
while (t<T):
	il = sys.stdin.readline().split(' ')
	N = int(il[0])
	M = int(il[1])
	
	print("%d" % (N-1 + M-1 + 2*(M-1)*(N-1)))
	
	t+=1

