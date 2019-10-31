// impl : Grundy-slight modification

#include<stdio.h>

char tx[5];

int main() {
    int t, n,i; char c, path, prev;
    scanf("%d",&t);
    while(t--) {
        scanf("%d",&n);
        prev = 'L';
        for (i=0;i<n;i++){
            scanf("%s",tx);
            if (prev == 'L') {
                if (tx[0] == 'l') {
                    path = '1';
                } else {
                    path = '0';
                    prev = 'H';
                }
            } else if (prev == 'H') {
                if (tx[0] == 'l') {
                    path = '0';
                } else {
                    path = '1';
                    prev = 'L';
                }
            }
        }
        if (n%2) {
            if (path == '1') {
                printf("lxh\n");
            } else {
                printf("hhb\n");
            }
        } else {
            if (path == '0') {
                printf("lxh\n");
            } else {
                printf("hhb\n");
            }
        }
    }
    return 0;
}
