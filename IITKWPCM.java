import java.math.BigInteger;
import java.util.Arrays;
import java.io.*;

public class IITKWPCM {
	
	public static void main(String[] args) throws Exception {
		
		//long t = System.currentTimeMillis();
		
		long LIM = 1000000000000000000L;
		long[] pks = new long[20000];
		boolean[] flag = new boolean[32000];
		
		int pki = 0;
		int lp = 0;
		for (int i=3; i*i<32000; i+=2) {
			lp = i;
			if (!flag[i]) {
				for (long j=i; j>=0 && j<=LIM; j*=i) {
					pks[pki++] = j;
				}
				
				for (int j=i*i; j<32000; j+=2*i) {
					flag[j] = true;
				}
			}
		}
		
		for (int i=lp; i<32000; i+=2) {
			if (!flag[i]) {
				for (long j=i; j>=0 && j<=LIM; j*=i) {
					pks[pki++] = j;
				}
			}
		}
		
		//System.out.println("pki="+pki);
		//for (int i=0; i<pki; ++i) {
		//	System.out.printf("%d\n", pks[i]);
		//}
		//System.out.println("====");
		
		Arrays.sort(pks);
		
		int T;
		BigInteger n, bx;
		
		BufferedReader sc = new BufferedReader(new InputStreamReader(System.in));
		String sT;
		
		T = Integer.parseInt(sc.readLine());
		for (int xxx=0; xxx<T; ++xxx) {
			String s = sc.readLine();
			
			if (s.equals("1")) {
				System.out.println("0");
				continue;
			}
			
			long ln = Long.parseLong(s);
			
			if (ln == 4) {
				System.out.println(ln-1);
				continue;
			}
			
			long oln = ln;
			
			//System.out.println("oln=" + oln);
			
			if (ln%2 == 0) {
				ln /= 2;
			}
			
			n = new BigInteger(""+ln);
			
			if ((ln%2 == 1) && n.isProbablePrime(10)) {
				System.out.println(oln-1);
			} else {
				
				// check p^2
				double testsqrt = Math.sqrt((double)ln);
				long x = (long)Math.floor(testsqrt);
				
				//System.out.println("sqrt(x)=" + x);
				
				if (x%2 == 1 && x*x == ln) {
					bx = new BigInteger(""+x);
					if (bx.isProbablePrime(10)) {
						System.out.println(oln-1);
						continue;
					}
				}
				
				// check p^3
				double tcube = Math.cbrt((double)ln);
				x = (long)Math.floor(tcube);
				
				//System.out.println("cbrt(x)=" + x);
				
				if (x%2 == 1 && x*x*x == ln) {
					bx = new BigInteger(""+x);
					if (bx.isProbablePrime(10)) {
						System.out.println(oln-1);
						continue;
					}
				}
				
				// check rest of case
				int r = Arrays.binarySearch(pks, ln);
				
				//System.out.println("r="+r);
				
				if (r >= 0) {
					System.out.println(oln-1);
				} else {
					System.out.println(1);
				}
			}
			
		}
		
		//System.err.println(System.currentTimeMillis() - t);
	}
}
