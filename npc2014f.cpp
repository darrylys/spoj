#include <stdio.h>

#define MAXN 100010
#define ll long long

char field[MAXN];
int need[26];
int owned[26];

int main() {
	
	int N, K;
	int xi, yi;
	char cyi[5];
	
	scanf("%d", &N);
	
	scanf("%s", field);
	
	scanf("%d", &K);
	for (int i=0; i<K; ++i) {
		scanf("%d %s", &xi, cyi);
		need[cyi[0]-'a'] = xi;
	}
	
	// [begin, end)
	int begin = 0, end = 0, minc = -1, mb, me;
	
	// the bit flag, if a particular plant needed in [a,b], bit 1<<x is 0. otherwise 1. So, if bitflag == 0
	// then plant requirement is fulfilled!
	int bitflag = 0;
	
	for (int i=0; i<26; ++i) {
		if (need[i]) {
			bitflag |= 1<<i;
		}
	}
	
	for (int i=0, plant; i<N; ++i) {
		plant = field[i]-'a';
		
		end++;
		owned[plant]++;
		
		if (owned[plant] == need[plant]) {
			bitflag &= ~(1<<plant);
		}
		
		while(1) {
				
			int beginPlant = field[begin]-'a';
			if (owned[beginPlant] > need[beginPlant]) {
				begin++;
				owned[beginPlant]--;
			} else {
				break;
			}
			
		}
		
		if (bitflag == 0) {
			if (minc == -1 || minc > (end-begin)) {
				minc = end-begin;
				//mb = begin;
				//me = end;
				//printf("ATTEMPT: minc=%d [%d,%d)\n", minc, mb, me);
			}
		}
	}
	
	if (minc > 0) {
		printf("%d\n", minc);
		//printf("FINAL: [%d,%d)\n", mb, me);
	} else {
		printf("Andy rapopo\n");
	}
	return 0;
}
