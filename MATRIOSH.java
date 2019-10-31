import java.io.*;
import java.util.*;

public class spojMATRIOSH {
    public static void main(String... args) throws Exception {
        int[] stack = new int[50000];
        int top;
        boolean res;
        BufferedReader sc = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st;
        String in;
        while ((in=sc.readLine())!=null) {
            if (in.length() == 0) continue;
            st = new StringTokenizer(in);
            top = 0;
            res = true;
            if (st.countTokens() % 2 == 1) res = false;
            while (st.hasMoreTokens() && res) {
                /*System.out.print("stack = ");
                for (int i=0; i<top; i++) {
                    System.out.print(stack[i]+" ");
                }
                System.out.println();
                */
                int now = Integer.parseInt(st.nextToken());
                
                if (now < 0) {
                    stack[top++] = now;
                } else {
                    if (top == 0) res = false;
                    else {
                        if (stack[top-1] < 0) {
                            if (now == -stack[top-1]) {
                                stack[top-1] = now;
                            } else {
                                res = false;
                            }
                        } else {
                            
                            long t = 0;
                            while (stack[top-1] > 0) {
                                t = t + stack[top-1];
                                top --;
                            }
                            if (t < (long)now && now == -stack[top-1]) {
                                stack[top-1] = now;
                            } else {
                                res = false;
                            }
                        }
                    }
                }
            }
            //System.out.println("top = " + top);
            if (res && top == 1) System.out.println(":-) Matrioshka!");
            else System.out.println(":-( Try again.");
        }
    }
}
