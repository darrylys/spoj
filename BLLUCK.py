
# AC 0.04s 23M SPOJ
# 
# Comments: Wow.
# 
# The formula is: \sigma i=[0..N] (i * C(N,i) * t(N-i) / N!)
# t(N) = number of derangements with N elements (https://en.wikipedia.org/wiki/Derangement)
# 
# Funnily enough, that sum is ALWAYS 1, (except for N=0 which is 0 of course). Tried in Excel for values up to 14.
# need more analysis why the sum is always 1.
#
# Space: O(1)
# Time: O(T)

import os
import re
import sys

def main():
    sys.stdin.readline()
    
    for r in sys.stdin:
        ra = int(r)
        if (ra == 0):
            print("0.000000")
        else:
            print("1.000000")

if __name__ == '__main__':
    main()
