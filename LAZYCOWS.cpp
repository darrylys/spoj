#include<stdio.h>
#include<algorithm>
#include<string.h>

#define MAXINT 200000000

using namespace std;

int field[1010][2];

typedef struct {
    int r;
    int x;
} Cell;

Cell cell[1010];
int dp[1010][1010][6]; //[n][k][d]
char flag[1010][1010][6];
int rangek[6][2];
int temprangek[6][2];

int _min(int a, int b) {
    return (a<b)?a:b;
}

int _max(int a, int b) {
    return (a>b)?a:b;
}

bool cmp(Cell a, Cell b) {
    if (a.x > b.x) return false;
    else if (a.x < b.x) return true;
    else return a.r < b.r;
}

int fill_field(int n) {
    memset(field, 0, sizeof(field));
    
    int lastp = 0;
    int lastx=0;
    
    for (int i=0; i<n; ++i) {
        if (lastx != cell[i].x) {
            lastp++;
            lastx = cell[i].x;
        }
        field[lastp][cell[i].r-1] = cell[i].x;
    }
    
    return lastp;
}

void printfield(int nacc) {
    for (int i=1; i<=nacc; ++i) {
        printf("%3d ", field[i][0]);
    }
    putchar('\n');
    for (int i=1; i<=nacc; ++i) {
        printf("%3d ", field[i][1]);
    }
}

void printdp(int n, int k) {
    for (int i=0; i<6; ++i) {
        printf("code = %d\n", i);
        
    }
}

int main() {
    int t, _n, _k, b, nacc;
    scanf("%d", &t);
    
    bool up, down, stat[2], prevgate[2], currgate[2];
    
    while (t--) {
        //memset(flag, false, sizeof(bool));
        scanf("%d %d %d", &_n, &_k, &b);
        
        
        for (int i=0; i<_n; ++i) {
            scanf("%d %d", &cell[i].r, &cell[i].x);
        }
        
        sort(cell, cell+_n, cmp);
        
        nacc = fill_field(_n);
        
        //printfield(nacc);
        //printf("\nOne-based => nacc=%d\n", nacc);
        
        //printf("================new case================\n");
        for (int i=0; i<=nacc; ++i) {
            memset(flag[i], 0, sizeof(flag[i]));
        }
        
        //initial condition
        up = field[1][0] > 0;
        down = field[1][1] > 0;
        
        dp[1][1][4] = 2; flag[1][1][4] = 1;
        dp[1][1][5] = 2; flag[1][1][5] = 1;
        if (up && down) {
            dp[1][2][0] = 2; flag[1][2][0] = 1;
            dp[1][2][1] = 2; flag[1][2][1] = 1;
            dp[1][2][2] = 2; flag[1][2][2] = 1;
            dp[1][2][3] = 2; flag[1][2][3] = 1;
        } else if (!up && down) {
            dp[1][2][0] = 2; flag[1][2][0] = 1;
            dp[1][1][1] = 1; flag[1][1][1] = 1;
            dp[1][2][2] = 2; flag[1][2][2] = 1;
            dp[1][1][3] = 1; flag[1][1][3] = 1;
        } else if (up && !down) {
            dp[1][2][0] = 2; flag[1][2][0] = 1;
            dp[1][2][1] = 2; flag[1][2][1] = 1;
            dp[1][1][2] = 1; flag[1][1][2] = 1;
            dp[1][1][3] = 1; flag[1][1][3] = 1;
        }
        
        rangek[0][0] = 2; rangek[0][1] = 2;
        rangek[1][0] = 1; rangek[1][1] = 2;
        rangek[2][0] = 1; rangek[2][1] = 2;
        rangek[3][0] = 1; rangek[3][1] = 2;
        rangek[4][0] = 1; rangek[4][1] = 1;
        rangek[5][0] = 1; rangek[5][1] = 1;
        
        for (int i=2; i<=nacc; ++i) {
            stat[0] = field[i][0] > 0; stat[1] = field[i][1] > 0;
            memset(temprangek, -1, sizeof(temprangek));
            
            for (int pg=0; pg<=2; ++pg) {
                prevgate[0] = (pg&1)>0;
                prevgate[1] = (pg&2)>0;
                
                for (int cg=0; cg<=3; ++cg) {
                    currgate[0] = (cg&1)>0;
                    currgate[1] = (cg&2)>0;
                    
                    for (int k=rangek[pg][0], dl, sk; k <= rangek[pg][1]; ++k) {
                        dl = 0;
                        
                        sk = 0;
                        for (int p=0;p<2;++p){
                            if (!prevgate[p]) {
                                dl += _max(field[i][0], field[i][1]) - _max(field[i-1][0], field[i-1][1]);
                            } else {
                                if (!currgate[p]) {
                                    dl += 1;
                                    sk ++;
                                } else {
                                    dl += stat[p];
                                    sk += stat[p];
                                }
                            }
                        }
                        
                        if (k+sk <= _k) {
                            int temp = (flag[i-1][k][pg]) ? dp[i-1][k][pg] : MAXINT;
                            
                            if (!flag[i][k+sk][cg]) {
                                dp[i][k+sk][cg] = temp + dl;
                                flag[i][k+sk][cg] = 1;
                            } else {
                                dp[i][k+sk][cg] = _min(dp[i][k+sk][cg], temp + dl);
                            }
                            if (temprangek[cg][1] < k+sk) temprangek[cg][1] = k+sk;
                            //printf("pg0-2, dp[%d][%d][%d]=%d, dl=%d\n", i-1, k, pg, dp[i-1][k][pg], dl);
                            //printf("pg0-2, dp[%d][%d][%d]=%d, dl=%d\n", i, k+sk, cg, dp[i][k+sk][cg], dl);
                        }
                    }
                }
            }
            
            for (int pg=3; pg<=5; pg +=2) {
            
                for (int cg=0; cg<=3; ++cg) {
                    currgate[0] = (cg&1)>0;
                    currgate[1] = (cg&2)>0;
                    for (int k=rangek[pg][0], dl; k <= rangek[pg][1]; ++k) {
                        dl = 0;
                        int sk = 0;
                        
                        for (int p=0;p<2;++p){
                            if (!currgate[p]) {
                                dl += 1;
                                sk++;
                            } else {
                                dl += stat[p];
                                sk += stat[p];
                            }
                        }
                        
                        if (k+sk <= _k) {
                            int temp = (flag[i-1][k][pg]) ? dp[i-1][k][pg] : MAXINT;
                        
                            if (!flag[i][k+sk][cg]) {
                                dp[i][k+sk][cg] = temp + dl;
                                flag[i][k+sk][cg] = 1;
                            } else {
                                dp[i][k+sk][cg] = _min(dp[i][k+sk][cg], temp + dl);
                                
                            }
                            
                            //printf("pg3&5, dp[%d][%d][%d]=%d, dl=%d\n", i-1, k, pg, dp[i-1][k][pg], dl);
                            //printf("pg3&5, dp[%d][%d][%d]=%d, dl=%d\n", i, k+sk, cg, dp[i][k+sk][cg], dl);
                            if (temprangek[cg][1] < k+sk) temprangek[cg][1] = k+sk;
                        }
                    }
                }
                
                for (int cg=4; cg<=5; ++cg) {
                    for (int k=rangek[pg][0], dl; k <= rangek[pg][1]; ++k) {
                        if (k+1 <= _k) {
                            int temp = (flag[i-1][k][pg]) ? dp[i-1][k][pg] : MAXINT;
                        
                            if (!flag[i][k+1][cg]) {
                                dp[i][k+1][cg] = temp + 2;
                                flag[i][k+1][cg] = 1;
                            } else {
                                dp[i][k+1][cg] = _min(dp[i][k+1][cg], temp + 2);
                            }
                            if (temprangek[cg][1] < k+1) temprangek[cg][1] = k+1;
                            //printf("pg3&5, dp[%d][%d][%d]=%d\n", i-1, k, pg, dp[i-1][k][pg]);
                            //printf("pg3&5, dp[%d][%d][%d]=%d\n", i, k+1, cg, dp[i][k+1][cg]);
                        }
                    }
                }
            }
            
            //pg=4
            for (int cg=4; cg<=5; ++cg) {
                for (int k=rangek[4][0], dl; k <= rangek[4][1]; ++k) {
                    int temp = (flag[i-1][k][4]) ? dp[i-1][k][4] : MAXINT;
                    
                    if (flag[i][k][cg]) {
                        //printf("occurred = %d, k=%d\n", dp[i][k][cg], k);
                        dp[i][k][cg] = _min(dp[i][k][cg], temp 
                                + 2*(_max(field[i][0], field[i][1]) - _max(field[i-1][0], field[i-1][1])));
                    } else {
                        //printf("first occurred = %d\n", dp[i][k][cg]);
                        dp[i][k][cg] = temp + 2*(_max(field[i][0], field[i][1]) - _max(field[i-1][0], field[i-1][1]));
                        flag[i][k][cg] = 1;
                    }
                    if (temprangek[cg][1] < k) temprangek[cg][1] = k;
                    //printf("pg4, dp[%d][%d][%d]=%d, temp=%d, diffmax=%d\n", i, k, cg, dp[i][k][cg]
                    //    , temp, 2*(_max(field[i][0], field[i][1]) - _max(field[i-1][0], field[i-1][1])));
                }
            }
            
            for (int p=0;p<6;++p) {
                rangek[p][1] = temprangek[p][1];
                //printf("temprangek[%d][%d]=%d\n", p, 1, temprangek[p][1]);
            }
        }
        
        int min=MAXINT;
        for (int i=0, t; i<6; ++i) {
            t = (flag[nacc][_k][i])? dp[nacc][_k][i] : MAXINT;
            //printf("final=>dp[%d][%d][%d]=%d\n", nacc, _k, i, dp[nacc][_k][i]);
            min =_min(min, t);
        }
        printf("%d\n", min);
    }
    
    return 0;
}