import java.math.BigInteger;
import java.io.*;
import java.util.*;

public class spojTREE {
    public static int[][] getPascalTriangle() {
        int[][] C = new int[33][33];
        
        C[0][0] = 1;
        for (int i=1; i<=32; ++i) {
            C[i][0] = 1;
            for (int j=1; j<i; ++j) {
                C[i][j] = C[i-1][j-1] + C[i-1][j];
            }
            C[i][i] = 1;
        }
        return C;
    }
    
    public static void main(String... args) throws IOException {
        BufferedReader sc = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st;
        
        BigInteger[] data = new BigInteger[20];
        BigInteger[] sigma = new BigInteger[20];
        
        BigInteger temp;
        
        data[0] = data[1] = BigInteger.ONE;
        sigma[0] = BigInteger.ONE;
        
        int[][] C = getPascalTriangle();
        
        int n, d;
        String in;
        
        while ((in=sc.readLine()) != null) {
            st = new StringTokenizer(in);
            n = Integer.parseInt(st.nextToken());
            d = Integer.parseInt(st.nextToken());
            
            if (n + d == 0) break;
            
            if (d <= 1) {
                System.out.printf("%d %d %d\n", n, d, 1);
            } else {
                
                for (int i=2; i<=d; ++i) {
                    
                    temp = BigInteger.ZERO;
                    
                    for (int x=1; x<=n; ++x) {
                        //temp += C[i][x]*(f(i-1)^x)*(sigma(0..(i-2))^(i-x)) 
                        temp = temp.add(new BigInteger(""+C[n][x])
                            .multiply(data[i-1].pow(x))
                            .multiply(sigma[i-2].pow(n-x)));
                    }
                    
                    data[i] = temp;
                    sigma[i-1] = sigma[i-2].add(data[i-1]);
                    
                }
                System.out.printf("%d %d %s\n", n, d, data[d].toString());
            }
        }
    }
}