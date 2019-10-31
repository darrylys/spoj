#include<stdio.h>
#include<string.h>

#define MAXINT 100000000
#define MININT -100000000

//little-endian representation
void binary_counter(bool* arr, int n) {
    for (int i=0; i<n; i++) {
        if (!arr[i]) {
            arr[i] = true;
            break;
        } else {
            arr[i] = false;
        }
    }
}

int main() {
    int n, d;
    bool arr[8];
    int p[8], sum = 0;
    int max[40];
    int min[40];
    int allmax;
    scanf("%d %d", &n, &d);
    
    for (int i=0; i<40; i++) {
        max[i] = MININT;
        min[i] = MAXINT;
    }
    
    for (int i=0; i<n; i++) {
        
        memset(arr, false, 8*sizeof(bool));
        
        for (int j=0; j<d; j++) {
            scanf("%d", &p[j]);
        }
        
        for (int j=0; j<(1<<(d-1)); j++) {
            
            sum = p[0];
            for (int k=1; k<d; k++) {
                if (arr[k-1]) {
                    sum += p[k];
                } else {
                    sum -= p[k];
                }
            }
            
            if (sum > max[j]) max[j] = sum;
            if (sum < min[j]) min[j] = sum;
            binary_counter(arr, d);
        }
    }
    
    allmax = MININT;
    for (int i=0; i<(1<<(d-1)); i++) {
        if (max[i] - min[i] > allmax) allmax = max[i]-min[i];
    }
    
    printf("%d\n", allmax);
    
    return 0;
}