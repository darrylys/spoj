/*
AC 0.13s 2.8M SPOJ

algo:
math

The tower can be constructed as follows.
Lets pick only N-1 smallest blocks and construct a tower out of it.
Lets say there are f(N-1) ways to construct such tower.

We can construct tower consisting of N blocks by adding the Nth block
from existing towers consisting of smaller N-1 blocks.

The Nth block is larger than any of the blocks that has been used in a tower
So, if we add this block in between existing 2 blocks in existing tower, it will
be guaranteed to support the blocks above it. The problem is whether the block
below will support it. All we need is to check how many placements are possible
i.e. how many blocks from N-1 that is capable of supporting the Nth block.

Since any possible uses the same block (N-1), no matter what configuration, the number
of placements to place the Nth block is the same.

So, the recurrence is: 
f(N) = Nb * f(N-1).
with Nb = number of blocks that can support Nth block.
The number of blocks with WidthNth - Width <= D.

This can be done in linear time.
All we need is to sacrifice O(N lg N) for sorting.

Time: O(N lg N)
Space: O(N)

*/

#include <stdio.h>
#include <algorithm>
#include <vector>

const int MOD = 1000000009;
typedef long long ll;

int main() {
	int N, D;

	scanf("%d %d", &N, &D);
	std::vector<int> blocks(N);

	for (int i=0, b; i<N; ++i) {
		scanf("%d", &b);
		blocks[i] = b;
	}

	std::sort(blocks.begin(), blocks.end());

	ll mul = 1;
	for (int i=N-1, bi=N-2; i>=0; ) {
	
		if (bi >= 0 && blocks[i] - blocks[bi] <= D) {
			bi--;
		} else {
			mul = (mul * (i-bi)) % MOD;
			i--;
		}
	
	}

	printf("%lld\n", mul);
	return 0;
}

