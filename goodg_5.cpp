#include <stdio.h>

#define ll long long
#define MAXN 1000010
//#define DEBUG

struct LINE {
	LINE() {
		this->slope = 0;
		this->y0 = 0;
	}
	
	LINE(int x, ll y1, int d) {
		this->slope = d;
		this->y0 = (ll)y1 + (ll)x*d;
	}
	
	int slope;
	ll y0;
};

struct FRAC {
	FRAC(ll up, ll down) {
		this->up = up;
		this->down = down;
		this->infiniteFlag = 0;
	}
	
	FRAC() {
		this->up = 0;
		this->down = 1;
		this->infiniteFlag = 0;
	}
	
	FRAC(char a) {
		this->infiniteFlag = 1;
	}
	
	char infiniteFlag;
	ll up;
	ll down;
};

LINE stack[MAXN];
FRAC intersections[MAXN];

#ifdef DEBUG
void printLine(LINE &a) {
	printf("LINE {%d %d}\n", a.slope, a.y0);
}

void pfr(FRAC f) {
	if (f.infiniteFlag != 1) {
		printf("{%lld/%lld} = %lf\n", f.up, f.down, f.up / (double) f.down);
	} else {
		printf("{+infinity}\n");
	}
}
#endif

int compareFrac(FRAC &a, FRAC &b) {
	if (a.infiniteFlag & b.infiniteFlag) {
		return 0;
	} else if (a.infiniteFlag) {
		return 1;
	} else if (b.infiniteFlag) {
		return -1;
	}
	
	ll lh = 0;
	ll rh = 0;
	
	lh = a.up * b.down;
	rh = a.down * b.up;
	
	if (lh < rh) {
		return -1;
	} else if (lh == rh) {
		return 0;
	} else {
		return 1;
	}
}

FRAC intersect(LINE &l1, LINE &l2) {
	ll up = l2.y0 - l1.y0;
	ll down = -l1.slope +l2.slope;
	
	if (down < 0) {
		up *= -1;
		down *= -1;
	}
	
	return FRAC(up, down);
}

int main() {
	int N, a, d;
	
	int esp = 0;
	
	// bases
	LINE BASE;
	BASE.slope = 0;
	BASE.y0 = 0;
	stack[esp] = BASE;
	
	intersections[esp] = FRAC('1');
	esp++;
	
	ll prevmax = 0;
	
	scanf("%d", &N);
	for (int x=0; x<N; ++x) {
		scanf("%d %d", &a, &d);
		
		LINE newLine(x, a+prevmax, d);
		
		#ifdef DEBUG
		printf("read: %d %d; prevmax=%lld\n", a, d, prevmax);
		printLine(newLine);
		#endif
		
		// stack crushing
		while (1) {
			if (esp == 0) {
				intersections[esp] = FRAC('1');
				stack[esp] = newLine;
				esp++;
				break;
			}
			
			LINE topLine = stack[esp-1];
			if (topLine.slope >= d) {
				#ifdef DEBUG
				printf("CRUSHING LINE slope=%d\t", topLine.slope);
				printLine(topLine);
				#endif
				
				esp--;
				continue;
			}
			
			FRAC top2below = intersections[esp-1];
			FRAC itrPoint = intersect(topLine, newLine);
			int fc = compareFrac(itrPoint, top2below);
			
			#ifdef DEBUG
			printf("compare intersections between : {\n");
			printLine(topLine);
			printLine(newLine);
			printf("}\n");
			printf("comparing FRAC: {\n");
			pfr(top2below);
			pfr(itrPoint);
			printf("}\n");
			printf("results=%d\n", fc);
			#endif
			
			// itrPoint >= top2below (crush the stack!)
			if (fc >= 0) {
				esp--;
				continue;
			} else {
				// add to intersections and line stack
				intersections[esp] = itrPoint;
				stack[esp] = newLine;
				esp++;
			}
			break;
		}
		
		// search the query here using binary search for NEXT minute (position searched = x+1)
		int u=0, v=esp, c;
		FRAC key(x+1, 1);
		LINE responsible(0,0,0);
		
		#ifdef DEBUG
		printf("KEY: ");
		pfr(key);
		printf("LINES ON STACK: {\n");
		for (int i=0; i<esp; ++i) {
			printf("LINE: ");
			printLine(stack[i]);
			printf("INTERSECTION: ");
			pfr(intersections[i]);
			printf("==================================\n");
		}
		printf("}\n");
		#endif
		
		while (1) {
            if (u>=v) {
                //printf("nearest is data %d %d %d %d\n", data[u], data[v-1], data[c], u-1);
				responsible = stack[v-1];
                break;
            } else {
                c = (u+v)/2;
				int fracCmpResult = compareFrac(key, intersections[c]);
				if (fracCmpResult > 0) {
					v = c;
				} else if (fracCmpResult < 0) {
					u = c+1;
				} else {
					// responsible line is found at stack[c]!
					responsible = stack[c];
					break;
				}
            }
        }
		
		prevmax = responsible.y0 - (ll)responsible.slope * (x+1);
		if (prevmax < 0) {
			prevmax = 0;
		}
		
		#ifdef DEBUG
		printf("responsible line: ");
		printLine(responsible);
		printf("%lld\n", prevmax);
		#endif
		
	}
	
	printf("%lld\n", prevmax);
	
	return 0;
}

