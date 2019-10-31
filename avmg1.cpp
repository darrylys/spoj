#include <stdio.h>

int main() {
	int T, L;
	char buf[60];
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &L);
		scanf("%s", buf);
		
		int Wpos = 0, Tpos = 0;
		for (int i=0; i<L; ++i) {
			if (buf[i] == 'T') {
				Tpos = i;
			} else if (buf[i] == 'W') {
				Wpos = i;
			}
		}
		
		if (Tpos > Wpos) {
			Tpos = L-1-Tpos;
			Wpos = L-1-Wpos;
		}
		
		printf("%d.000000000000\n", Wpos*Wpos - Tpos*Tpos);
	}
}
