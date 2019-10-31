#include<stdio.h>
#include<stdlib.h>
#define MAX_N 105

typedef struct {
    int enter;
    int exit;
} Person;

int com ( const void* a, const void* b ) {
    Person* arg1 = (Person*) a;
    Person* arg2 = (Person*) b;
    if( arg1->exit < arg2->exit ) return -1;
    else if( arg1->exit == arg2->exit ) return 0;
    else return 1;
}

int _max(int a, int b) {return (a>b)?a:b;}

int main() {
    int tst;
    Person person[MAX_N];
    int cut[MAX_N], arr[MAX_N], perm[MAX_N], show[MAX_N];
    scanf("%d",&tst);
    while(tst--){
        int n,i,stc, max = -1, u, v, near, key, j, kk;
        scanf("%d",&n);
        memset(arr,0,n*4);
        for (i=0;i<n;i++){
            scanf("%d%d", &person[i].enter, &person[i].exit);
        }
        //printf("thisss\n");
        qsort(person, n, sizeof(person[0]), com);
        //for (i=0;i<n;i++){
        //    printf("%d %d\n", person[i].enter, person[i].exit);
       // }
        stc = 0;
        max = 1;
        kk=0;
        //printf("-\n");
        for (i=0;i<n;i++) {
            u = 0; v = i;
            key = person[i].enter;
            while (1) {
                if (u>=v) {
                    near = u-1;
                    break;
                } else {
                    int c = (u+v)/2;
                    if (key > person[c].exit) {
                        u = c+1;
                    } else if (key < person[c].exit) {
                        v = c;
                    } else {
                        near = c;
                        break;
                    }
                }
            }
            cut[i] = near;
            //printf("--\n");
            if (arr[cut[i]+1] == 0) {
                perm[kk] = cut[i]+1;
                show[cut[i]+1] = kk;
                kk++;
            }
            //arr[cut[i]+1]++;

            //printf("near = %d\n", near);
            for (j=show[cut[i]+1]; j<kk; j++) {
                arr[perm[j]]++;
            }
            //printf("idx=%d, max=%d, near=%d\n", i, max, near);
        }
        max=-1;
        for (i=0;i<kk;i++) {
            if (max<arr[perm[i]]) max=arr[perm[i]];
        }
        printf("%d\n", max);
    }
}
