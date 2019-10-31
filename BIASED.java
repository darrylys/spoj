import java.io.*;
import java.util.*;

public class spojBIASED {
    public static void main(String... args) throws Exception {
        BufferedReader sc = new BufferedReader(new InputStreamReader(System.in));
        int t = Integer.parseInt(sc.readLine());
        for (int xx = 0; xx < t; xx ++) {
            sc.readLine();
            int d = Integer.parseInt(sc.readLine());
            int[] h = new int[d];
            StringTokenizer st;
            for (int k = 0; k<d; k++) {
                st = new StringTokenizer(sc.readLine());
                st.nextToken();
                h[k] = Integer.parseInt(st.nextToken());
            }
            
            java.util.Arrays.sort(h);
            long acc = 0;
            for (int k = 1; k<=d; k++) {
                acc = acc + (long)Math.abs(h[k-1]-k);
            }
            System.out.println(acc);
        }
    }
}