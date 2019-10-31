import java.math.BigInteger;
import java.io.*;

public class TPC07 {
	private static final int[] COEF = new int[] {
		1,1,1,1,1,2,2,2,2,2,4,4,4,4,4,6,6,6,6,6,9,9,9,9,9,13,13,13,13,13,18,18,18,18,18,24,24,24,24,24,31,31,31,31,31,39,39,39,39,39,
		45,45,45,45,45,52,52,52,52,52,57,57,57,57,57,63,63,63,63,63,67,67,67,67,67,69,69,69,69,69,69,69,69,69,69,67,67,67,67,67,63,63,
		63,63,63,57,57,57,57,57,52,52,52,52,52,45,45,45,45,45,39,39,39,39,39,31,31,31,31,31,24,24,24,24,24,18,18,18,18,18,13,13,13,13,
		13,9,9,9,9,9,6,6,6,6,6,4,4,4,4,4,2,2,2,2,2,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	
	// not included. actual limit = 159.
	private static final int LIM_COEF = 160;
	
	public static void main(String[] args) throws Exception {
		BufferedReader sc = new BufferedReader(new InputStreamReader(System.in));
		
		String in;
		while((in=sc.readLine())!=null){
			int N = Integer.parseInt(in);
			
			//System.out.println("N=" + N);
			
			int[] x = new int[10];
			x[0] = N%50;
			int lx = 1;
			
			//System.out.println("x[0]=" + x[0]);
			
			for (int i=1; ; ++i) {
				x[i] = x[i-1]+50;
				//System.out.println("x[" + i + "]=" + x[i]);
				if (x[i] >= LIM_COEF || x[i] > N) {
					break;
				}
				lx++;
			}
			
			//System.out.println("lx=" + lx);
			
			int sn = (N-x[lx-1])/50 + 4;
			
			//System.out.println("sn=" + sn);
			
			BigInteger top = new BigInteger("" + sn);
			for (int i=1; i<4; ++i) {
				top = top.multiply(new BigInteger("" + (sn-i)));
			}
			top = top.divide(new BigInteger("24"));
			
			//System.out.println("top=" + top);
			
			BigInteger sum = BigInteger.ZERO;
			int tn = sn;
			
			for (int i=lx-1; i>=0; --i) {
				//System.out.println("tn=" + tn);
				
				// top * A[x[i]]
				sum = sum.add(top.multiply(new BigInteger("" + COEF[x[i]])));
				
				// update top, top = top * (n+1) / (n-3)
				top = top.multiply(new BigInteger("" + (tn+1))).divide(new BigInteger("" + (tn-3)));
				tn++;
			}
			
			System.out.println(sum);
		}
		
	}
}

