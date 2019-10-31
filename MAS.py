
# AC 0.46s 33M SPOJ PYTHON 3.5
# 
# Algo: ad hoc
#
# Remembered that you might need to implement trees?
# I forgot that the F(A) is always asking for the whole array
# 
# F(A) can be simplified to:
# F(A) = N * (\sigma i=1..N (A[i])^2) - (\sigma i=1..N A[i])^2
# 
# Simply maintain the array A and sum2 for (\sigma i=1..N (A[i])^2) and sum for (\sigma i=1..N A[i])^2.
# if there are requests to update the array A.
#
# sum2 and sum can be maintained simply by simple arithmetic functions
# query 2
# sum2 = sum2 - A[x]^2 + (A[x]+v)^2
# sum = sum + v
# A[x] += v
# 
# query 1
# sum2 = sum2 - A[x]^2 + v^2
# sum = sum - A[x] + v
# A[x] = v
# 
# Space: O(N)
# Time: O(T*Q), O(1) per query

import os
import sys

MOD = 2760727302517

def main():
    st = sys.stdin.readline().strip()
    T = int(st)
    t = 0
    
    while t<T:
        nq = sys.stdin.readline().strip().split(' ')
        N = int(nq[0])
        Q = int(nq[1])
        
        A = [int(x) for x in sys.stdin.readline().strip().split(' ')]
        
        sum2 = 0
        sum = 0
        
        for a in A:
            sum2 += a**2
            sum += a
            
        sum2 %= MOD
        sum %= MOD
        
        print("Case %d:" % (t+1))
        
        q = 0
        while q < Q:
            query = sys.stdin.readline().split(' ')
            if query[0] == '1':
                x = int(query[1]) - 1
                v = int(query[2])
                
                sum2 = sum2 - A[x]**2 + v**2
                sum = sum - A[x] + v
                A[x] = v
                
            elif query[0] == '2':
                x = int(query[1]) - 1
                v = int(query[2])
                
                sum2 = sum2 + 2*A[x]*v + v**2
                sum = sum + v
                A[x] += v
                
            else:
                print("%d" % (((N*sum2)%MOD - (sum**2)%MOD + MOD)%MOD))
            
            q+=1
        
        t += 1
    
    

if __name__ == '__main__':
    main()
