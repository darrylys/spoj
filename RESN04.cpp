#include<cstdio>

int main() {
	int t, n, res, temp;
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		res = 0;
		for (int i=1; i<=n; i++) {
			scanf("%d",&temp);
			res += temp/i;
		}
		if (res % 2 == 0) printf("BOB\n");
		else printf("ALICE\n");
	}
}