#include<stdio.h>

#define MEOF -1000000000

int data[1000010];
int maxfrom[1000010];
int maxidx[1000010];
int minfrom[1000010];
int minidx[1000010];

int getint() {
    char c;
    char flag = 1;
    int x = 0;
    
    while ((c=getchar())=='\n' || c=='\r' || c==' ');
    do {
        if (c==-1) {
            return MEOF;
        }
        if (c>='0' && c<='9') {
            x = x*10 + c-'0';
        } else if (c=='-') {
            flag=-1;
        }
    } while ((c=getchar())>='0' && c <= '9');
    return x*flag;
}


int main() {
    int n;
    int p[5];
    int pdx[5];
    int mdx[3];
    int max;
    int ph;
    
    while ((n=getint())!=MEOF) {
        for (int i=0; i<n; ++i) {
            data[i] = getint();
        }
        
        maxfrom[n-1] = data[n-1];
        minfrom[n-1] = data[n-1];
        maxidx[n-1] = n-1;
        minidx[n-1] = n-1;
        
        for (int i=n-2; i>=0; i--) {
            if (data[i] >= maxfrom[i+1]) {
                maxfrom[i] = data[i];
                maxidx[i] = i;
            } else {
                maxfrom[i] = maxfrom[i+1];
                maxidx[i] = maxidx[i+1];
            }
            
            if (data[i] <= minfrom[i+1]) {
                minfrom[i] = data[i];
                minidx[i] = i;
            } else {
                minfrom[i] = minfrom[i+1];
                minidx[i] = minidx[i+1];
            }
        }
        
        // hill side
        ph = 0;
        max=-1;
        for (int i=0; i<n; ++i) {
            switch (ph) {
                case 0: {
                    p[ph] = data[i];
                    pdx[ph] = i;
                    ph++;
                } break;
                
                case 1: {
                    if (data[i] < p[ph-1]) {
                        p[ph-1] = data[i];
                        pdx[ph-1] = i;
                    } else {
                        p[ph] = data[i];
                        pdx[ph] = i;
                        ph++;
                    }
                } break;
                
                case 2: {
                    if (data[i] > p[ph-1]) {
                        p[ph-1] = data[i];
                        pdx[ph-1] = i;
                    } else {
                        // compute the highest possible score..
                        int score = p[1]-p[0] + p[1]-minfrom[i];
                        if (score > max) {
                            max = score;
                            mdx[0] = pdx[0];
                            mdx[1] = pdx[1];
                            mdx[2] = minidx[i];
                        }
                        if (data[i] < p[0]) {
                            int tmax = maxfrom[i+1];
                            if (tmax >= p[1]) { //move!
                                p[0] = data[i];
                                pdx[0] = i;
                                ph = 1;
                            } else {
                                int dp1 = tmax-data[i];
                                int dp0 = p[1]-p[0];
                                int d = p[1]-tmax;
                                if (dp1 > dp0 + d) {
                                    p[0] = data[i];
                                    pdx[0] = i;
                                    ph=1;
                                }
                            }
                        }
                    }
                } break;
            }
        }
        
        // valleyside
        ph=0;
        for (int i=0; i<n; ++i) {
            switch (ph) {
                case 0: {
                    p[ph] = data[i];
                    pdx[ph] = i;
                    ph++;
                } break;
                
                case 1: {
                    if (data[i] > p[0]) {
                        p[0] = data[i];
                        pdx[0] = i;
                    } else {
                        p[1] = data[i];
                        pdx[1] = i;
                        ph=2;
                    }
                } break;
                
                case 2: {
                    if (data[i] < p[1]) {
                        p[1] = data[i];
                        pdx[1] = i;
                    } else {
                        int score = p[0]-p[1] + maxfrom[i]-p[1];
                        if (score > max) {
                            max = score;
                            mdx[0] = pdx[0];
                            mdx[1] = pdx[1];
                            mdx[2] = maxidx[i];
                        }
                        if (data[i] > p[0]) {
                            int tmin = minfrom[i+1];
                            if (tmin <= p[1]) {
                                p[0] = data[i];
                                pdx[0] = i;
                                ph=1;
                            } else {
                                int dp1 = data[i]-tmin;
                                int dp0 = p[0]-p[1];
                                int d = tmin-p[1];
                                if (dp1 > dp0+d) {
                                    p[0] = data[i];
                                    pdx[0] = i;
                                    ph=1;
                                }
                            }
                        }
                    }
                } break;
            }
        }
        
        if (max==-1) printf("-1\n");
        else {
            printf("%d %d %d\n", mdx[0]+1, mdx[1]+1, mdx[2]+1, max);
        }
    }
    return 0;
}
