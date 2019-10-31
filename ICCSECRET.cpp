#include <stdio.h>
#include <string.h>

//  01234567
//  AAAAAAAA
//
// 012345678
// 123456789

bool _find(int used, char * pattern, int patternLen, int * buf, int bufLastLetterPos) {
	
	// base case
	if (bufLastLetterPos == patternLen) {
		return true;
	}
	
	// recursive case
	bool ok = false;
	if (pattern[bufLastLetterPos] == 'A') {
		
		for (int i=buf[bufLastLetterPos]+1; !ok && i<=9; ++i) {
			if (used & (1<<i)) {
				continue;
			} else {
				buf[bufLastLetterPos+1] = i;
				ok |= _find(used | (1<<i), pattern, patternLen, buf, bufLastLetterPos+1);
			}
		}
		
		
	} else {
		
		for (int i=1; !ok && i<buf[bufLastLetterPos]; ++i) {
			if (used & (1<<i)) {
				continue;
			} else {
				buf[bufLastLetterPos+1] = i;
				ok |= _find(used | (1<<i), pattern, patternLen, buf, bufLastLetterPos+1);
			}
		}
	}
	
	return ok;
}

void find(char * pattern, int patternLen) {
	int buf[10];
	bool f;
	
	for (int i=1; i<=9; ++i) {
		buf[0] = i;
		f = _find(1<<i, pattern, patternLen, buf, 0);
		if (f) {
			for (int i=0; i<=patternLen; ++i) {
				printf("%d", buf[i]);
			}
			putchar('\n');
			return;
		}
	}
}

int main() {
	int T;
	char pattern[10];
	scanf("%d", &T);
	while (T--) {
		scanf("%s", pattern);
		find(pattern, strlen(pattern));
	}
	return 0;
}
