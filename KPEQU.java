import java.math.BigInteger;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;

public class spojKPEQU {
    public static int[] prime = new int[10015];
    public static boolean[] flag = new boolean[10015];
    
    public static int sieve(int n) {
    
        int c = 0, i;
        prime[c++] = 2;
        
        for (i=3; i*i <= n; i +=2) {
            if (!flag[i]) {
                prime[c++] = i;
                for (int j=i*i; j<n; j+=2*i) flag[j] = true;
            }
        }
        
        for (; i<n; i+=2) {
            if (!flag[i]) prime[c++] = i;
        }
        
        return c;
    }
    
    public static BigInteger solve(int n) {
        int ori, exp; 
        BigInteger mul = BigInteger.ONE;
        
        for (int i=0; prime[i] <= n; ++i) {
            ori = n;
            exp = 0;
            
            while (ori > 0) {
                exp += ori/prime[i];
                ori /= prime[i];
            }
            
            mul = mul.multiply(new BigInteger("" + (2*exp + 1)));
        }
        
        return mul;
    }
    
    public static void main(String... args) throws IOException {
        int nop = sieve(10015);
        int x;
        
        BufferedReader sc = new BufferedReader(new InputStreamReader(System.in));
        
        while (true) {
            x = Integer.parseInt(sc.readLine());
            if (x == 0) break;
            
            System.out.println(solve(x));
        }
    }
}