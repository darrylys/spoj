import java.io.*;

public class spojABSYS {
    public static void main(String[] args) throws IOException {
        BufferedReader sc = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(sc.readLine()), res;
        String tj; String[] right, left;
        while (true) {
            tj = sc.readLine();
            if (tj == null) break;
            if (!tj.equals("")) {
                right = tj.split(" = ");
                left = right[0].split(" \\+ "); 
                if (right[1].contains("machula")) {
                    res = Integer.parseInt(left[0]) + Integer.parseInt(left[1]);
                    System.out.println(right[0]+" = "+res);
                } else if (left[0].contains("machula")) {
                    res = Integer.parseInt(right[1]) - Integer.parseInt(left[1]);
                    System.out.println(res+" + "+left[1]+" = "+right[1]);
                } else {
                    res = Integer.parseInt(right[1]) - Integer.parseInt(left[0]);
                    System.out.println(left[0]+" + "+res+" = "+right[1]);
                }
            }
        }
    }
}