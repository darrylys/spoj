#include<stdio.h>

#define MAXN 50010

int freq[4];
char arr[MAXN*2];
char two[MAXN*2];

void swap(int a, int b) {
    char temp = two[a];
    two[a] = two[b];
    two[b] = temp;
}

int main() {
    int n, min, src;
    char col, wcolor;
    scanf("%d", &n);
    
    scanf("%s", arr);
    
    for (int i=0; i<2*n; ++i) {
        ++freq[arr[i]-'A'];
    }
    
    for (int i=0; i<2*n; ++i) {
        
        min = MAXN;
        for (int j=0; j<4; ++j) {
            if (j+'A' != arr[i] && (i==0 || j+'A' != two[i-1]) 
                && min > freq[j]
                && freq[j] < n) {
                min = freq[j];
                col = j+'A';
            }
        }
        
        if (min == MAXN) { //required swap operation
            //printf("---\n");
            for (int j=0; j<4; ++j) {
                if (freq[j] == n-1) {
                    wcolor = j+'A';
                    break;
                }
            }
            //printf("wcolor = %c---\n", wcolor);
            for (int j=0; j<i; ++j) {
                
                //if ok swap with two[j], swap & break else continue searching;
                if ((j==0 || two[j-1] != wcolor) && two[j+1] != wcolor && arr[j] != wcolor &&
                    two[j] != two[i-1] && two[j] != arr[i]) {
                    //printf("---i\n");
                    two[i] = wcolor;
                    swap(j, i);
                    two[2*n] = '\0';
                    printf("%s\n", two);
                    return 0;
                }
            }
            //printf("---\n");
        }
        
        two[i] = col;
        freq[col-'A']++;
        //printf("col=%c\n", col);
    }
    
    two[2*n] = '\0';
    printf("%s\n", two);
    return 0;
}