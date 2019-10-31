#include<cstdio>
#include<cstring>

int stack[1005];
int top;

int main() {
    int n, t, car;
    int turn;
    bool f;
    while (scanf("%d", &n) && n) {
        f=true;
        turn = 1;
        top = 0;
        memset(stack, 0, n*sizeof(int));
        while (n--) {
            scanf("%d", &car);
            //for (int i=0; i<top; i++) printf("%d ", stack[i]);
            //putchar('\n');
            rerun:
            //printf("car = %d, turn = %d\n", car, turn);
            if (car == turn) {
                turn++;
            } else {
                if (top > 0 && stack[top-1] == turn) {
                    turn++;
                    top--;
                    goto rerun;
                } else {
                    stack[top] = car;
                    top++;
                }
            }
        }
        //printf("top=%d\n", top);
        while (top--) {
            if (stack[top] == turn) {
                turn++;
                //top--;
            }
            else {
                f=false;
                break;
            }
        }
        if (f) printf("yes\n");
        else printf("no\n");
    }
    return 0;
}
