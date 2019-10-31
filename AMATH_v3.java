import java.io.*;
import java.math.*;

public class AMATH3 {
	static BigInteger x2=new BigInteger("2"), x5=new BigInteger("5");
	static double l2=Math.log(2), l5=Math.log(5);
	static int[] get(BigInteger n, int k2, int k5, BigInteger m) {
		BigInteger bs=n,b2;
		double cmn=5000,t;int e2=-1,e5=-1;
		for(int i=0;i<=k5;++i){
			b2=bs;
			if (k2==0) break;
			for(int j=0;j<=k2;++j){
				if (n.multiply(b2).mod(m).equals(n)){
					t=i*l5+j*l2;
					if(t<cmn){
						cmn=t;e2=j;e5=i;k2-=2;
					}
					break;
				}
				b2=b2.modPow(x2,m);
			}
			bs=bs.modPow(x5,m);
		}
		return new int[]{e2,e5};
	}
	public static void main(String[] args) throws Exception {
		BufferedReader sc = new BufferedReader(new InputStreamReader(System.in));
		String in; BigInteger m,m2,m5,n; int k;
		while((in=sc.readLine())!=null){
			String[] inp=in.split(" ");
			int l0=inp[0].length(),il=l0;
			k=Integer.parseInt(inp[1]);
			while (inp[0].charAt(il-1) == '0') {
				il--;
			}
			if (l0-il>=k){
				System.out.println(1);continue;
			}else if (l0>il){
				System.out.println(-1);continue;
			}
			n=new BigInteger(inp[0]);
			int[] r=new int[]{-1};
			m2=BigInteger.ONE.shiftLeft(k);
			m5=x5.pow(k);
			System.out.println("m2=" + m2 + "m5=" + m5);
			switch(inp[0].charAt(l0-1)-'0'){
				case 1:
				case 3:
				case 7:
				case 9: {
					int[] r2=get(n.mod(m2),k-1,0,m2);
					int[] r5=get(n.mod(m5),2,k-1,m5);
					System.out.printf("r2={%d,%d} r5={%d,%d}%n",r2[0],r2[1],r5[0],r5[1]);
					r=new int[]{Math.max(r2[0],r5[0]),Math.max(r2[1],r5[1])};
				} break;
				
				case 5: {
					if (n.mod(m5).equals(BigInteger.ZERO)) {
						System.out.println("m5");
						r=get(n.mod(m2),k-1,0,m2);
					}
				} break;
				
				case 0: 
				System.out.println("m0");
				break;
				
				default: {
					if (n.mod(m2).equals(BigInteger.ZERO)) {
						System.out.println("m5=" + m5 + " nmodm5=" + n.mod(m5));
						r=get(n.mod(m5),2,k-1,m5);
					}
				} break;
			}
			if (r[0]>0) {
				System.out.println(x5.pow(r[1]).shiftLeft(r[0]));
			} else {
				System.out.println(-1);
			}
		}
	}
}