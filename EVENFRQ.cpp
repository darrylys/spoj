/*
AC, 3.71s, 25M, slowest in SPOJ :(

algo:
classic MO algorithm
updates are just 50 max
every updates can be performed in O(N) because there are only 50 of them (max)
the rest of the queries can be handled with classic MO algorithm
the problem can be treated as if having 50 test cases (for each updates)
and classic MO algorithn to handle each of them separately
*/

#include <cstdio>
#include <cmath>
#include <algorithm>
#include <string.h>

using namespace std;

#define ll long long
//#define _DEBUG
//#define _TIMED

#ifdef _TIMED
#include <time.h>
#endif

typedef struct _P {
	int L, R;
	int bn;
	int qn;
} PII;

const int MAXV = 5100010;
const int MAXL = 100010;
const int MAXQ = 100010;

PII query[MAXQ];

int tally[MAXV];
int arr[MAXL];
bool qans[MAXQ];
int changed[MAXL];
bool idxchanged[MAXL];

bool comp(const PII& a, const PII& b) {
	if (a.bn != b.bn) {
		return a.bn < b.bn;
	}
	return (a.R < b.R);
}

int main() {
	#ifdef _TIMED
	clock_t START = clock();
	#endif
	
	int T, N, Q, cq, cmd, lcq, cn=1, sqrv;
	scanf("%d", &T);
	
	while (T--) {
		
		cq = 0;
		scanf("%d %d", &N, &Q);
		
		#ifdef _DEBUG
		printf("N=%d, Q=%d\n", N, Q);
		#endif
		
		sqrv = sqrt(N);
		
		for (int i=1; i<=N; ++i) {
			scanf("%d", &arr[i]);
		}
		
		printf("Case %d:\n", cn++);
		
		for (int i=0; i<=Q; ++i) {
			if (i == Q) {
				cmd = 1;
			} else {
				scanf("%d", &cmd);
			}
			
			if (cmd == 2) {
				int L, R;
				scanf("%d %d", &L, &R);
				
				query[i].qn = i;
				query[i].L = L;
				query[i].R = R;
				query[i].bn = L / sqrv;
				
			} else {
				
				int QE = i;
				int QS = cq;
				int nchanged = 0;
				
				#ifdef _DEBUG
				printf("QS=%d, QE=%d\n", QS, QE);
				#endif
				
				if (QE > QS) {
					
					sort(query+QS, query+QE, comp);
					
					#ifdef _DEBUG
					printf("sorted query: \n");
					for (int j=QS; j<QE; ++j) {
						printf("{ qn=%d, L=%d, R=%d, bn=%d }\n", query[j].qn, query[j].L, query[j].R, query[j].bn);
					}
					#endif
					
					int rp=0;
					int lp=1;
					//int even=0;
					int odd=0;
					
					for (int j=QS; j<QE; ++j) {
						int L = query[j].L;
						int R = query[j].R;
						
						#ifdef _DEBUG
						printf("Query: {%d %d}\n", query[j].L, query[j].R);
						#endif
						
						while (rp < R) {
							rp++;
							
							#ifdef _DEBUG
							printf("rp<R, rp=%d, R=%d\n", rp, R);
							#endif
							
							if (!idxchanged[rp]) {
								changed[nchanged++] = rp;
								idxchanged[rp] = true;
							}
							
							tally[arr[rp]]++;
							
							#ifdef _DEBUG
							printf("arr[%d]=%d, tally[%d]=%d\n", rp, arr[rp], arr[rp], tally[arr[rp]]);
							#endif
							
							if (tally[arr[rp]]&1) {
								odd++; //even -= tally[arr[rp]] != 1;
							} else {
								odd--; //even++;
							}
							
							#ifdef _DEBUG
							printf("odd=%d\n", odd);
							#endif
						}
						
						while (rp > R) {
							#ifdef _DEBUG
							printf("rp>R, rp=%d, R=%d\n", rp, R);
							#endif
							
							tally[arr[rp]]--;
							
							#ifdef _DEBUG
							printf("arr[%d]=%d, tally[%d]=%d\n", rp, arr[rp], arr[rp], tally[arr[rp]]);
							#endif
							
							if (tally[arr[rp]]&1) {
								odd++; //even--;
							} else {
								odd--; //even += tally[arr[rp]] != 0;
							}
							
							#ifdef _DEBUG
							printf("odd=%d\n", odd);
							#endif
							
							rp--;
						}
						
						while (lp < L) {
							#ifdef _DEBUG
							printf("lp<L, lp=%d, L=%d\n", lp, L);
							#endif
							
							tally[arr[lp]]--;
							
							#ifdef _DEBUG
							printf("arr[%d]=%d, tally[%d]=%d\n", lp, arr[lp], arr[lp], tally[arr[lp]]);
							#endif
							
							if (tally[arr[lp]]&1) {
								odd++; //even--;
							} else {
								odd--; //even += tally[arr[lp]] != 0;
							}
							
							#ifdef _DEBUG
							printf("odd=%d\n", odd);
							#endif
							
							lp++;
						}
						
						while (lp > L) {
							#ifdef _DEBUG
							printf("lp>L, lp=%d, L=%d\n", lp, L);
							#endif
							
							lp--;
							
							if (!idxchanged[lp]) {
								changed[nchanged++] = lp;
								idxchanged[lp] = true;
							}
							
							tally[arr[lp]]++;
							
							#ifdef _DEBUG
							printf("arr[%d]=%d, tally[%d]=%d\n", lp, arr[lp], arr[lp], tally[arr[lp]]);
							#endif
							
							if (tally[arr[lp]]&1) {
								odd++; //even -= tally[arr[lp]] != 1;
							} else {
								odd--; //even++;
							}
							
							#ifdef _DEBUG
							printf("odd=%d\n", odd);
							#endif
						}
						
						//printf("%lld\n", ans);
						#ifdef _DEBUG
						printf("odd=%d\n", odd);
						#endif
						qans[query[j].qn] = odd == 0;
					}
					
					for (int j=QS; j<QE; ++j) {
						printf("%s\n", qans[j] ? "Yes" : "No");
					}
				}
				
				// for next test cases
				for (int j=0; j<nchanged; ++j) {
					tally[arr[changed[j]]] = 0;
					idxchanged[changed[j]] = false;
				}
				//memset(idxchanged, false, sizeof(idxchanged));
				
				if (i == Q) {
					break;
				}
				
				cq = i+1;
				
				if (cmd == 1) {
					int L, R, V;
					scanf("%d %d %d", &L, &R, &V);
					
					for (int j=L; j<=R; ++j) {
						arr[j] = V;
					}
					
				} else { // cmd == 0
					int X, V;
					scanf("%d %d", &X, &V);
					
					arr[X] += V;
					
				}
			}
		}
		
		//memset(tally, 0, sizeof(tally));
	}
	
	#ifdef _TIMED
	double T_ELAPSED = (double)(clock() - START) / CLOCKS_PER_SEC;
	fprintf(stderr, "%lf\n", T_ELAPSED);
	#endif
}

