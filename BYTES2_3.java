import java.util.*;
import java.io.*;

class Person {
	int enter;
	int exit;
}

public class spojBYTES2_3 {
	public static void main(String... args) throws Exception {
		BufferedReader sc = new BufferedReader(new InputStreamReader(System.in));
		Set<Person> person = new TreeSet<Person>(
			new Comparator<Person>() {
				public int compare(Person a, Person b) {
					return a.exit-b.exit;
				}
			}
		);
		Person dummy;
		int[] arr = new int[105];
		int ptr;
		int tst = Integer.parseInt(sc.readLine());
		for (int xx = 0; xx < tst; xx++) {
			int n = Integer.parseInt(sc.readLine());
			for (int i=0;i<n;i++) arr[i] = 0;
			ptr = 0;
			StringTokenizer st;
			for (int i=0;i<n;i++) {
				st = new StringTokenizer(sc.readLine());
				dummy = new Person();
				dummy.enter = Integer.parseInt(st.nextToken());
				dummy.exit = Integer.parseInt(st.nextToken());
				person.add(dummy);
			}
			for (Iterator it = person.iterator(); it.hasNext(); ) {
				dummy = (Person)(it.next());
				boolean f = false;
				for (int i=0; i<ptr; i++) {
					if (dummy.enter > arr[i]) {
						arr[i] += dummy.exit;
						f=true;
						break;
					}
				}
				if (!f) {
					arr[ptr++] += dummy.exit;
				}
			}
			System.out.println(ptr);
			person.clear();
		}
	}
}

