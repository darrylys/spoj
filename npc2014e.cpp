#include <stdio.h>
#include <string.h>

int printbuf(int *buf) {
	for(int i=0;i<5;++i)printf("%d ", buf[i]);
	printf("\n");
}


int main() {
	int T, N, mt, rest;
	int buf[5];
	scanf("%d", &T);
	while (T--) {
		memset(buf, 0, sizeof(buf));
		
		scanf("%d", &N);
		for (int i=0, x; i<N; ++i) {
			scanf("%d", &x);
			buf[x]++;
		}
		
		mt = 0;
		
		//1-2
		if (buf[1] == buf[2]) {
			mt += buf[1];
			printf("%d\n", mt);
			continue;
		}
		
		if (buf[2] > buf[1]) {
			mt += buf[1];
			
			// 2* 3* 4*
			buf[3] += buf[1];
			buf[2] -= buf[1];
			buf[1] -= buf[1];
			
			mt += (buf[2]/3) * 2;
			buf[3] += (buf[2]/3) * 2;
			buf[2] = buf[2]%3;
			
			if (buf[2] == 1) {
				if (buf[4] > 0) {
					mt += 1;
				} else if (buf[3] > 1) {
					mt += 2;
				} else {
					mt = -1;
				}
				
			} else if (buf[2] == 2) {
				mt += 2;
			}
		} else {
			// 2 < 1
			
			//printf("mt=%d\n", mt);
			//printbuf(buf);
			
			// 1* 3* 4*
			mt += buf[2];
			buf[3] += buf[2];
			buf[1] -= buf[2];
			buf[2] -= buf[2];
			
			//printf("mt=%d\n", mt);
			//printbuf(buf);
			
			mt += (buf[1]/3)*2;
			buf[3] += buf[1]/3;
			buf[1] = buf[1]%3;
			
			//printf("mt=%d\n", mt);
			//printbuf(buf);
			
			if (buf[1] == 1) {
				if (buf[3] >= 1) {
					mt += 1;
				} else if (buf[4] >= 2) {
					mt += 2;
				} else {
					mt = -1;
				}
				
			} else if (buf[1] == 2) {
				if (buf[4] >= 1) {
					mt += 2;
				} else if (buf[3] >= 2) {
					mt += 2;
				} else {
					mt = -1;
				}
			}
			
			//printf("mt=%d\n", mt);
			//printbuf(buf);
			
		}
		
		if (mt == -1) {
			printf("Tresi gagal memuaskan gadisnya.\n");
		} else {
			printf("%d\n", mt);
		}
	}
}