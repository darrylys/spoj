#include <stdio.h>
#include <assert.h>

#define ll long long

int cmd[1000010];
int label[1000010];
int flag[1000010];
int trav[1000010];
int temp[1000010];

void getLineCh(char *buf, int lim) {
	char x;
	int i=0;
	while ((x=getchar()) == '\r' || x == '\n' || x == ' ' || x == '\t');
	
	do {
		assert(i < lim);
		
		buf[i++] = x;
	} while ((x=getchar()) !=EOF && x != '\r' && x != '\n');
	buf[i] = '\0';
}

int main() {
	int N;
	ll M;
	
	char input[20];
	
	scanf("%d %lld", &N, &M);
	int eip = 0, pos, ilabel;
	
	for (int i=0; i<N; ++i) {
		getLineCh(input, 20);
		//printf("read %s\n", input);
		
		//scanf("%s", input);
		if (input[0] == 'c') {
			// c++;
			cmd[eip++] = 'c';
			
		} else if (input[0] == 'g') {
			// goto:
			
			sscanf(input, "goto %d;", &pos);
			//printf("goto: pos=%d, eip=%d\n", pos, eip);
			cmd[eip++] = pos;
			
		} else {
			sscanf(input, "%d:", &ilabel);
			//printf("LABEL: label=%d, eip=%d\n", ilabel, eip);
			
			label[ilabel] = eip;
			cmd[eip++] = 'n';
		}
	}
	
	//printf("eip=%d\n", eip);
	
	ll c = 0;
	int trvi = 0;
	
	for (int i=0; i<N;) {
		
		//printf("cmd[%d]=%c\n", i, (char)cmd[i]);
		
		if (flag[i]) {
			// cycle is detected!
			
			//printf("i=%d, trvi=%d\n", i, trvi);
			
			int pit = flag[i]-1;
			int st = 0;
			for (int j=pit; j<trvi; ++j) {
				//printf("cmd[trav[%d]]=%d (%c)\n", j, cmd[trav[j]], (char)cmd[trav[j]]);
				
				if (cmd[trav[j]] == 'c') {
					temp[st++] = trav[j];
				}
			}
			
			if (st == 0) {
				printf("TLE\n");
			} else {
				//printf("st=%d, M=%d, c=%d\n", st, M, c);
				
				printf("%d\n", temp[(M-c-1+st)%st]+1);
			}
			
			c=M;
			break;
		}
		
		trav[trvi] = i;
		//printf("trav[%d]=%d | ", trvi, trav[trvi]);
		
		flag[i] = ++trvi;
		//printf("flag[%d]=%d\n", i, flag[i]);
		
		if (cmd[i] == 'c') {
			c++;
			if (c == M) {
				printf("%d\n", i+1);
				break;
			}
			
			i++;
		} else if (cmd[i] == 'n') {
			i++;
		} else {
			i = label[cmd[i]];
			//printf("goto! %d, cmd=%d\n", i, cmd[i]);
		}
		
		
	}
	
	if (c < M) {
		printf("WA\n");
	}
	
	return 0;
}
