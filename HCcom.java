import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.Queue;

public class spojHCcom {
    public static void main(String... args) throws Exception {
        final String L = "L", H = "H";
        HashMap<String,Integer> hap = new HashMap<String,Integer>();
        HashSet<Integer> set;
        hap.put(L,1); hap.put(H,0);
        Queue<String> q = new LinkedList<String>();
        q.offer(L); q.offer(H);
        int num = 2;
        String temp;
        for (int ttttt=0;  ttttt<5;  ttttt++) {
            
            for (int i=0; i<num; i++) {
                String f = q.poll();
                q.offer(f+L);
                q.offer(f+H);
            }
            
            num*=2;
            
            set = new HashSet<Integer>();
            for (int i=0; i<num; i++) {
                String f = q.poll();
                
                int len = f.length();
                for (int j=1; j<len; j++) {
                    if (f.charAt(j) == f.charAt(j-1)) {
                        temp = f.substring(0,j-1) + H;
                    } else {
                        temp = f.substring(0,j-1) + L;
                    }
                    if (j+1 < len) temp += f.substring(j+1,len);
                    set.add(hap.get(temp));
                }
                int st = 0;
                while (set.contains(st)) {
                    st++;
                }
                hap.put(f,st);
                set.clear();
                System.out.println(f + " => " + st);
                q.offer(f);
            }
        }
    }
}