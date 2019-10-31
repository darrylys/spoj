#include<cstdio>
#define l long long

int sum[] = {0,1,-1,2,-2,3,-3,4,-4,5};

l translate(l a) {
    l lim = 100;
    l mul = 90;
    l res = 0;
    l div = 45;
    int part = 2;
    if (a>=10) {
        res += 5;
    }
    while (a>=lim) {
        if (part%2) {
            res += mul*5;
            mul *= 100LL;
            //printf("res=%lld\n", res);
            //printf("div=%lld\n", mul);
        } else {
            res -= div;
            div *= 100LL;
            //printf("res=%lld\n", res);
            //printf("div=%lld\n", div);
        }
        lim *= 10LL;
        part++;
    }

    int dig = 0;
    l temp = a;
    l near10 = 1;
    l sgn;
    while (temp>0) {
        temp/=10;
        near10 *= 10LL;
        dig++;
    }
    near10 /= 10;
    if (dig%2) {
        if ((a+1)%2) {
            temp = a/10;
            res += (temp - near10/10)*5 + sum[a%10-1];
            temp = a;
            sgn = -1;
            while (temp > 0) {
                res += sgn*(temp%10);
                temp /=10;
                sgn *= -1;
            }
        } else {
            temp = a/10;
            res += (temp - near10/10)*5 + sum[a%10];
        }
    } else {
        l after, before =0, acc, level=1;
        sgn = 1;
        near10 /= 10;
        temp = a;
        while (temp > 0) {
            after = temp/10;
            acc = (after-near10)*45LL*level + (temp%10)*(temp%10 - 1)/2*level + (temp%10)*(before+1);
            acc *= sgn;
            res += acc;
            before += (temp%10)*level;
            level *= 10LL;
            temp /=10;
            near10 /= 10;
            sgn *= -1;
        }
    }
    return res;
}

int main() {
    l a;
    while (scanf("%lld", &a) && a) {
        printf("%lld\n", translate(a));
    }
    return 0;
}
