import java.math.BigInteger;
import java.io.*;
import java.util.StringTokenizer;

public class spojREC {
    public static final BigInteger TWO = new BigInteger("2");
    
    public static int[][] mul(int[][] a, int[][] b, int MOD) {
        int[][] c = new int[2][2];
        c[0][0] = (int)(((long)a[0][0]*b[0][0] + (long)a[0][1]*b[1][0])%((long)MOD));
        c[0][1] = (int)(((long)a[0][0]*b[0][1] + (long)a[0][1]*b[1][1])%((long)MOD));
        c[1][0] = (int)(((long)a[1][0]*b[0][0] + (long)a[1][1]*b[1][0])%((long)MOD));
        c[1][1] = (int)(((long)a[1][0]*b[0][1] + (long)a[1][1]*b[1][1])%((long)MOD));
        return c;
    }
    
    public static int[][] pow(BigInteger n, int mod, int a, int b, int[][] base, int[][] id) {
        if (n.equals(BigInteger.ZERO)) return id;
        if (n.equals(BigInteger.ONE)) return base;
        int[][] A = pow(n.shiftRight(1), mod, a, b, base, id);
        if (n.mod(TWO).equals(BigInteger.ONE)) {       //odd mod
            return mul(mul(A,A,mod),base,mod);
        } else {
            return mul(A,A,mod);
        }
    }
    
    public static int _pow(BigInteger n, int mod, int a, int b, int[][] base, int[][] id) {
        int[][] mtr = pow(n,mod,a,b,base,id);
        return (int)((mtr[0][0] + (long)mtr[1][0])%mod);
    }
    
    public static void main(String... args) throws Exception {
        BufferedReader sc = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter out = new BufferedWriter(new OutputStreamWriter(System.out));
        StringTokenizer st;
        int[][] id = new int[][] {{1,0},{0,1}};
        int[][] base;
        
        BigInteger _n, _a, _b, _m;
        int m, a, b;
        int testcase = Integer.parseInt(sc.readLine());
        for (int xx = 0; xx < testcase; xx++) {
            st = new StringTokenizer(sc.readLine());
            _a = new BigInteger(st.nextToken());
            _b = new BigInteger(st.nextToken());
            _n = new BigInteger(st.nextToken());
            _m = new BigInteger(st.nextToken());
            m = _m.intValue();
            a = _a.mod(_m).intValue();
            b = _b.mod(_m).intValue();
            base = new int[][] {{a,0},{b,1}};
            out.write(String.valueOf(_pow(_n, m, a, b, base, id)));
            out.write("\n");
            out.flush();
        }
    }
}