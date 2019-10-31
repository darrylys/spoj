import java.math.BigInteger;
import java.io.*;
import java.util.HashMap;
import java.util.Map;

public class pib {
	/*static class P {
		int px, pb, pn;
		
		P(int x, int b, int n) {
			px = x;
			pb = b;
			pn = n;
		}
		
	}
	*/
	static int tr(int x, int b) {
		return x*10000+b;
	}
	/*
	static int[] rt(int k) {
		int[] p = new int[2];
		p[0] = k/10000;
		p[1] = k%10000;
		return p;
	}
	*/
	static BigInteger getC(int n, int r, BigInteger prev) {
		if (r <= 0) return BigInteger.ZERO;
		
		return prev.multiply(new BigInteger(""+(r))).divide(new BigInteger(""+(n-r+1)));
	}
	
	
	public static void R_main(String[] args) {
		//System.out.println(getC(Integer.parseInt(args[0]), Integer.parseInt(args[1]), new BigInteger(args[2])));
		
		int x = Integer.parseInt(args[0]);
		int b = (int) Math.ceil((x-4)/Math.PI);
		
		System.out.println(b);
		
	}
	
	public static void main(String[] args) throws Exception {
		BufferedReader sc = new BufferedReader(new InputStreamReader(System.in));
		//Queue<P> queue = new LinkedList<P>();
		Map<Integer, BigInteger> comb = new HashMap<Integer, BigInteger>();
		
		String in;
		while ((in=sc.readLine())!=null) {
			if (in.equals("-1")) break;
			
			int x = Integer.parseInt(in);
			
			if (x < 4) {
				System.out.println("1");
				continue;
			}
			
			int b = (int) Math.ceil((x-4)/Math.PI);
			int r = 0;
			BigInteger bres = BigInteger.ZERO;
			int res = 0;
			
			comb.clear();
			//queue.clear();
			
			int beginState = tr(x, b);
			comb.put(beginState, BigInteger.ONE);
			
			//queue.add(new P(x, b, b));
			
			int ncx = x, ncb = b, ncn = b;
			
			//while (!queue.isEmpty()) {
			while (ncx >= 0) {
				
				//P itop = queue.poll();
				int cx = ncx;//itop.px;
				int cb = ncb;//itop.pb;
				int cn = ncn;//itop.pn;
				
				int cstate = tr(cx, cb);
				BigInteger cval = comb.get(cstate);
				
				if (cx - cb * Math.PI < 4.0) {
					bres = bres.add(cval);
					
					if (cb > 0) {
						int next = tr(cx-1, cb-1);
						//queue.add(new P(cx-1, cb-1, cn));
						
						ncx = cx-1;
						ncb = cb-1;
						ncn = cn;
						
						if (!comb.containsKey(next)) {
							comb.put(next, getC(cn, cb, cval));
						}
					} else {
						break;
					}
					
				} else {
					// break down node
					BigInteger nxOff = getC(cn, cb, cval);
					
					// LH
					int next1 = tr(cx, cb+1);
					//queue.add(new P(cx, cb+1, cn+1));
					ncx = cx;
					ncb = cb+1;
					ncn = cn+1;
					
					comb.put(next1, cval);
					
					// RH
					int next2 = tr(cx-1, cb);
					comb.put(next2, cval.add(nxOff));
					
				}
				
			}
			
			String strRes = bres.toString();
			int lStrRes = strRes.length();
			for (int i=0, el; i<lStrRes; i+=50) {
				System.out.println(strRes.substring(i, Math.min(i+50, lStrRes)));
			}
			
		}
		
	}
}
