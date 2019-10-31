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
    int arr[MAX_N];
    scanf("%d",&tst);
    while(tst--){
        int n, i, j, max = -1, u, v, key, near;
        scanf("%d", &n);
        memset(arr,0,n*sizeof(int));
        for (i=0;i<n;i++){
            scanf("%d%d", &person[i].enter, &person[i].exit);
        }
        qsort(person, n, sizeof(person[0]), com);

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

            for (j = near+1; j<=i; j++) {
                arr[j]++;
            }
        }
        for (i=0;i<n;i++) {
            if (arr[i] > max) max = arr[i];
        }
        printf("%d\n", max);
    }
}
