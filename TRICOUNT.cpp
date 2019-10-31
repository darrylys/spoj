#include<cstdio>
#define l long long
int main(){
    int i,t,n;
    scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        if(n%2) printf("%lld\n",((l)n*(n+1)*(n+2))/6 + (4LL*(n/2)*(n/2)*(n/2)+9LL*(n/2)*(n/2)+5LL*(n/2))/6);
        else printf("%lld\n",((l)n*(n+1)*(n+2))/6 + (4LL*(n/2)*(n/2)*(n/2)+3LL*(n/2)*(n/2)-(n/2))/6);
    }
}