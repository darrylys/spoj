//complexity (n^2 log n)

#include<cstdio>

#define MAXN 1005
#define HEAPTREE 0
#define FIND true
#define UPDATE false

int data[MAXN][3*MAXN];
int dp[MAXN][MAXN];
int arraylocmap[MAXN];
int treelocmap[MAXN];
int unsorted[MAXN];

void printArray(char* text, int* array, int n) {
    printf("%s\n", text);
    for (int i=1;i<=n;i++) {
        printf("%d ", array[i]);
    }
    putchar('\n');
}

void build_tree(int start, int end, int node) {
    if (start == end) {
        treelocmap[unsorted[start]] = node;
        return;
    } else {
        build_tree(start, (start+end)/2, node*2);
        build_tree((start+end)/2+1, end, node*2+1);
    }
}

void build_array_reverse_map(int n) {
    for (int i=0;i<n;i++) {
        arraylocmap[unsorted[i]] = i+1;
    }
}

int find_index(int item, int n, int place) {
    int start = arraylocmap[item];
    int index = treelocmap[item];
    
    while (index>0) {
        if (index%2 == 0) {
            index/=2;
        } else {
            start += data[place][index-1]; //data is negative.
            index/=2;
        }
    }
    return start;
}

int find_index_plus_update(int item, int n, int place) {
    int start = arraylocmap[item];
    int index = treelocmap[item];
    
    while (index>0) {
        if (index%2 == 0) {
            data[place][index]--;
            index/=2;
        } else {
            data[place][index]--;
            start += data[place][index-1]; //data is negative.
            index/=2;
        }
    }
    return start;
}

void make_zero(int place, int n) {
    for (int i=1;i<=n; i++) {
        int now = treelocmap[i];
        while (now > 0) {
            if (data[place][now] < 0) {
                data[place][now] = 0;
                now /= 2;
            } else break;
        }
    }
}

int _min(int a, int b) {
    return (a<=b)?a:b;
}

int main() {
    int t, n;
    bool mode;
    scanf("%d",&t);
    while (t--) {
        scanf("%d",&n);
        for (int i=0;i<n;i++) scanf("%d",&unsorted[i]);
        build_array_reverse_map(n);
        build_tree(0,n-1,1);
        //printArray("reverse_map:", arraylocmap, n);
        //printArray("treelocmap:", treelocmap, n);
        
        for (int i=1;i<=n;i++) {
            dp[i][i] = arraylocmap[i];
            make_zero(i, n);
            find_index_plus_update(i, n, i);
        }
        for (int diff = 1; diff <n; diff++) {
            mode = FIND;
            for (int min = 1; min < n; min++) {
                
                int max = min + diff;
                
                dp[max][min] = _min(dp[max-1][min] + (diff+1)*(find_index_plus_update(max, n, min)), 
                                             dp[max][min+1] + (diff+1)*(find_index(min, n, min+1)));
            }
        }
        /*printf("DP table:\n");
        for (int i=1; i<=n; i++) {
            for (int j=1; j<=n; j++) {
                printf("%3d ", dp[i][j]);
            }
            putchar('\n');
        }*/
        printf("%d\n", dp[n][1]);
    }
    return 0;
}