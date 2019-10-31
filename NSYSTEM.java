import java.io.*;

public class spojNSYSTEM {
	public static void main(String[] args) throws IOException {
		BufferedReader sc = new BufferedReader(new InputStreamReader(System.in));
		int nums = Integer.valueOf(sc.readLine()).intValue();
		String[] token;
		int len, mul, temp, sum;
		int[] ace = new int[2];
		String conv, result;
		char[] ids = {'m', 'c', 'x', 'i'};
		for (int k=0;k<nums;k++) {
			token = sc.readLine().split(" ");
			ace[0]=ace[1]=0;
			for (int j=0;j<2;j++) {
				len = token[j].length();
				for (int i=len-1; i>=0; i--) {
					mul = 0;
					temp=0;
					switch(token[j].charAt(i)) {
						case 'i': mul = 1; break;
						case 'x': mul = 10; break;
						case 'c': mul = 100; break;
						case 'm': mul = 1000; break;
						default: mul = 0; break;
					}
					if (i-1 >= 0) {
						if (token[j].charAt(i-1) >= '0' && token[j].charAt(i-1) <= '9') {
							temp = (token[j].charAt(i-1)-'0')*mul;
						} else {
							temp = mul;
						}
					} else {
						temp = mul;
					}
					ace[j]+=temp;
				}
				//System.out.println(ace[j]);
			}
			sum = ace[0]+ace[1];
			conv = ""+sum;
			result = "";
			len = conv.length();
			temp = 4-len;
			for (int i=0;i<len;i++) {
				
				if (conv.charAt(i)>'1') {
					result+=conv.charAt(i)+""+ids[temp];
				} else if (conv.charAt(i)=='1') {
					result+=ids[temp];
				}
				temp++;
			}
			System.out.println(result);
		}
	}
}

