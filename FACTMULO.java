import java.math.BigInteger;
import java.io.*;
import java.util.StringTokenizer;

public class FACTMULO {
	public static void main(String[] args) throws Exception {
		BufferedReader sc = new BufferedReader(new InputStreamReader(System.in));
		
		String in;
		
		int T = Integer.parseInt(sc.readLine());
		
		for (int xxx = 0; xxx < T; ++xxx) {
			StringTokenizer st = new StringTokenizer(sc.readLine());
			
			BigInteger P = new BigInteger((String)st.nextElement());
			BigInteger N = new BigInteger((String)st.nextElement());
			
			BigInteger p = P;
			BigInteger sum = BigInteger.ZERO;
			
			while (true) {
				BigInteger[] NdivmodP = N.divideAndRemainder(P);
				
				BigInteger NdivP = NdivmodP[0];
				if (NdivP.equals(BigInteger.ZERO)) {
					break;
				}
				
				BigInteger NmodP = NdivmodP[1];
				
				sum = sum.add(
					P.multiply(NdivP).multiply(NdivP.subtract(BigInteger.ONE)).shiftRight(1)
						.add(NmodP.add(BigInteger.ONE).multiply(NdivP))
				);
				
				P = P.multiply(p);
			}
			
			System.out.println(sum);
		}
		
	}
}
