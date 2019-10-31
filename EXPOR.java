/*
AC 0.38s 695M SPOJ

it requires big integer. sucks balls!

Algo:
just remember that in discrete math, Expectation is just glorified "average over all possible inputs"
the problem is simply:
given A1, A2, ..., AN ; 2 <= N <= 10^5, 0 <= A < 2^31
find average Ai|Aj , | = bitwise or, for all 1 <= i<j <= N

calculate each bits separately and combine the final result

let Ai|Aj = b30 b29 b28 ... b3 b2 b1 b0; bx = {0,1}; the binary representation of Ai|Aj
this is equivalent to:
b30 * 2^30 + b29 * 2*29 + ... + b1 * 2^1 + b0 * 2^0

now, group all 2^30 together, 2^29 together, and so on.
in group 2^x, only need to handle xth bit of Ai.
find the total pairsum of xth bit in A array.

the total pairsum of xth bit can simply be calculated in constant time
Xx = (n1*(N-1) + (N-n1)*n1)/2;

where n1 = number of 1 bits in xth bit of A array
derived this way:

let:
BX = bx1 bx2 bx3 ... bxn; bx = {0,1}; example: 0101001010100101
represents the array of xth bit of all elements in array A.
Now, pair up all elements in the array, how many of them will produce bit 1?

lets assume that (i|j) and (j|i) is different and also counting (i|i)
let n1 = number of 1 bits in BX; n1 = 7 in the above example

lets do pair operation
lets pair:
	bxi | {bx1, bx2, bx3, ..., bxn}; 1 <= i <= n
	
it can be seen that if bxi == 1, all pairs will produce bit 1 also.
and if bxi == 0, the number of 1 bit produced will be n1.

so, the total number of 1 bit is:
n1 * N + (N - n1) * n1
where N - n1 is the number of bxi == 0

now, set (i|j) and (j|i) is the same and remove (i|i)
we get:
(n1 * N + (N - n1) * n1 - n1)/2
Since the number of (i|i) is simply n1

Do all that for all x, 0 <= x < 31

the combined expression of all Ai|Aj summed will be of the form:

let S = X0 * 2^30 + X1 * 2^29 + ... + X30 * 2^0

while the average is:
S / (N*(N-1)/2)

Time: O( T * N lg N)
Space: O( N )

*/

import java.math.BigInteger;
import java.io.*;

public class EXPOR {
	static int MAXN = 100001;
	static int[] A = new int[MAXN];
	
	public static void main(String[] args) throws Exception {
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		
		int T = Integer.parseInt(in.readLine());
		
		for (int zz=0; zz<T; ++zz) {
			
			int N = Integer.parseInt(in.readLine());
			
			String[] sin = in.readLine().split(" ");
			for (int i=0; i<sin.length; ++i) {
				A[i] = Integer.parseInt(sin[i]);
			}
			
			BigInteger s = BigInteger.ZERO;
			for (int i=0; i<31; ++i) {
				
				int n1 = 0;
				for (int j=0; j<N; ++j) {
					if ((A[j]&(1<<i)) > 0) {
						n1++;
					}
				}
				
				long q = ((long)n1*(N-1) + (long)(N-n1)*(n1))>>1;
				
				s = s.add(new BigInteger(q+"").shiftLeft(i));
			}
			
			BigInteger d = new BigInteger(((long)(N) * (N-1) / 2) + "");
			
			BigInteger g = s.gcd(d);
			System.out.printf("%d/%d%n", s.divide(g), d.divide(g));
			
		}
		
	}
}
