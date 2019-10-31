// AC!
// need to improve the backtracking
// largest prime gap is 281 from 436273010 to 436273290
// possible above 300, why?

// algorithm: backtracking + pruning
// improvements
// forward checking. fills the only one possibility first. Only too recursive step if no other possibilities exist.
// all primes above (hi-lo) can only appear once in sequence
// longest sequence <= 500.

#include <stdio.h>
#include <string.h>
#include <algorithm>

#define MAXP (100000)
#define ll long long

using namespace std;

bool flag[MAXP];
int prime[10000];

// prime factors of integers
ll pf[500][50];

// number of prime factors
int nfac[500];

// number of possible assignable primes
bool usedPrime[500];
int primecount[500];

// result
ll primedist[500];

int buildPrime() {
	
	prime[0] = 2;
	int p = 1;
	
	for (int i=3; i < MAXP; i += 2) {
		if (!flag[i]) {
			prime[p++] = i;
			if (i < 317) {
				for (int j = i*i; j < MAXP; j += 2*i) {
					flag[j] = true;
				}
			}
		}
	}
	
	return p;
}

int factor(ll x, int nprimes, ll * primeFactor) {
	int p = 0;
	
	for (int i=0; x > 1 && i<nprimes; ++i) {
		if (x % prime[i] == 0) {
			primeFactor[p++] = prime[i];
			
			while (x % prime[i] == 0) {
				x /= prime[i];
			}
		}
	}
	
	if (x > 1) {
		primeFactor[p++] = x;
	}
	
	return p;
}

// assumption usedpf[nidx][prime];
bool isPrimeUsed(int nidx, ll p, ll lo, ll hi) {
	if (p > (hi-lo)) {
		return false;
	}
	
	return usedPrime[(int)p];
}

void setPrimeUsed(int nidx, ll p, ll lo, ll hi, bool flag) {
	if (p > (hi-lo)) {
		return;
	}
	
	usedPrime[(int)p] = flag;
}

// lo + hi no change
bool _find(int nidx, ll lo, ll hi, int nUniqPrimes) {
	//printf("_find(%d)\n", nidx);
	
	if (nidx >= ((int)(hi-lo+1))) {
		return true;
	}
	
	// already assigned, forward request
	if (primedist[nidx]) {
		return _find(nidx+1, lo, hi, nUniqPrimes);
	}
	
	//ll primeAllocated[500];
	int modifyIdx[500];
	int idxAllocated[500];
	
	bool res = false;
	ll d;
	int px;
	
	//printf("begin\n");
	for (int i=0; !res && i<nfac[nidx]; ++i) {
		
		d = pf[nidx][i];
		
		if (!isPrimeUsed(nidx, d, lo, hi)) {
			
			px = 0;
			memset(modifyIdx, 0, sizeof(modifyIdx));
			
			//printf("prime=%lld\n", d);
			
			setPrimeUsed(nidx, d, lo, hi, true);
			primedist[nidx] = d;
			
			//primeAllocated[px] = d;
			idxAllocated[px] = nidx;
			px++;
			
			bool fail = false;
			int lastj;
			
			// plan:
			// loop {
			// erase other primes
			// account for forced assignments
			// record all primes that are set. record all indexes are changed
			// }
			
			// rollback op {
			// unset all primes that are set. unset all decr indexes
			// }
			
			bool working = true;
			ll cup = d;
			int startidx = nidx;
			
			while (working) {
				working = false;
				
				//printf("cup=%lld\n", cup);
				
				// erase other primes
				for (ll lj=startidx%cup; !fail && lo + lj <= hi; lj+=cup) {
					int j = (int)lj;
					
					if (!primedist[j]) {
						modifyIdx[j]++;
						
						primecount[j]--;
						if (primecount[j] == 0) {
							//printf("startidx=%d, cup=%d, primecount[%d]=%d, pos=%lld\n", startidx, cup, j, 0, j+lo);
							
							fail = true;
							working = false;
							break;
						}
					}
				}
				
				//printf("cup=%lld, fail=%d, working=%d\n", cup, fail, working);
				
				bool foundPrime = false;
				// account for forced assignments
				for (int j=0; !fail && j <= (int)(hi-lo); ++j) {
					//int j = (int)lj;
					
					// only one prime option available, grab it!
					if ((!primedist[j]) && (primecount[j] == 1)) {
						working = true;
						
						//printf("j=%d primedist[%d]\n", j, j);
						//for (int o=0; o<=(int)(hi-lo); ++o) {
						//	printf("%lld ", primedist[o]);
						//}
						//putchar('\n');
						
						for (int k=0; k<nfac[j]; ++k) {
							if (!isPrimeUsed(j, pf[j][k], lo, hi)) {
								//printf("prime not used\n");
								
								setPrimeUsed(j, pf[j][k], lo, hi, true);
								primedist[j] = pf[j][k];
								cup = pf[j][k];
								//primeAllocated[px] = cup;
								idxAllocated[px] = j;
								startidx = j;
								px++;
								foundPrime = true;
								
								break;
							}
						}
						break;
					}
					
					if (foundPrime) break;
				}
				//printf("working=%d\n", working);
			}
			
			
			
			if (!fail) {
				res |= _find(nidx+1, lo, hi, nUniqPrimes);
			}
			
			if (!res || fail) {
				//rollback crazy
				for (int x=0; x<px; ++x) {
					setPrimeUsed(nidx, primedist[idxAllocated[x]], lo, hi, false);
					primedist[idxAllocated[x]] = 0;
				}
				for (int j=0; j <= (int)(hi-lo); ++j) {
					primecount[j] += modifyIdx[j];
				}
				
				//setPrimeUsed(nidx, d, lo, hi, false);
				//primedist[nidx] = 0;
				//for (ll lj=nidx+d/*%d*/; lj <= (ll)lastj && lo + lj <= hi; lj+=d) {
				//	primecount[(int)lj]++;
				//}
			}
		}
	}
	
	return res;
}

void find(ll lo, ll hi, int nprimes) {
	
	int ix = 0;
	for (ll i=lo; i<=hi; ++i) {
		int idx = (int)(i-lo);
		nfac[idx] = primecount[idx] = factor(i, nprimes, pf[idx]);
		
		/*
		printf("%lld:", i);
		for (int m=0; m<nfac[idx]; ++m) {
			printf(" %lld", pf[idx][m]);
		}
		printf("\n");
		*/
	}
	
	memset(primedist, 0, sizeof(primedist));
	memset(usedPrime, 0, sizeof(usedPrime));
	
	_find(0, lo, hi, -1);
	
	int nk = (int)(hi-lo+1);
	printf("%lld", primedist[0]);
	for (int i=1; i<nk; ++i) {
		printf(" %lld", primedist[i]);
	}
	putchar('\n');
}

int main() {
	int nprimes = buildPrime();
	
	ll LO, HI;
	while (1) {
		scanf("%lld %lld", &LO, &HI);
		//printf("read: [%lld %lld]\n", LO, HI);
		if (LO == 0 && HI == 0) break;
		find(LO, HI, nprimes);
	}
}
