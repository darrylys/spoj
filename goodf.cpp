#include<stdio.h>
#include<algorithm>

//#define NDEBUG
#define MAXN 1000010
#define ll long long

struct TEAM {
	int dx;
	int dy;
	int code;
	int member;
	int teamId;
	
	ll dist2;
	ll cost;
};

TEAM enemy[MAXN];
int enemyId[MAXN];

int quadrant(int dx, int dy) {
	if (dx >= 0 && dy >= 0) { return 0; }
	if (dx < 0 && dy >= 0) { return 2; }
	if (dx >= 0 && dy < 0) { return 1; }
	return 3;
}

int checkInLine(int ea, int eb) {
	int a = enemyId[ea];
	int b = enemyId[eb];
	
	if (enemy[a].code == enemy[b].code) {
		ll lh = (ll)enemy[a].dx * enemy[b].dy;
		ll rh = (ll)enemy[a].dy * enemy[b].dx;
		
		if (lh == rh) {
			return 1;
		}
	}
	return 0;
}

// sort on gradient, then distance
bool funcsort(int a, int b) {
	if (enemy[a].code == enemy[b].code) {
		ll lh = (ll)enemy[a].dx * enemy[b].dy;
		ll rh = (ll)enemy[a].dy * enemy[b].dx;
		
		if (lh == rh) {
			return enemy[a].dist2 < enemy[b].dist2;
			
		} else {
			return lh < rh;
		}
	} else {
		return enemy[a].code < enemy[b].code;
	}
}

int main() {
	int N, Q, X, Y, xi, yi, mi, ti;
	scanf("%d %d %d %d", &N, &Q, &X, &Y);
	
	for (int i=1; i<=N; ++i) {
		scanf("%d %d %d", &xi, &yi, &mi);
		enemyId[i] = i;
		enemy[i].teamId = i;
		enemy[i].dx = xi - X;
		enemy[i].dy = yi - Y;
		enemy[i].code = quadrant(enemy[i].dx, enemy[i].dy);
		enemy[i].member = mi;
		enemy[i].dist2 = ((ll)enemy[i].dx * enemy[i].dx) + ((ll)enemy[i].dy * enemy[i].dy);
	}
	
	std::sort(enemyId+1, enemyId+1 + N, funcsort);
	
	#ifdef NDEBUG
	for (int i=1; i<=N; ++i) {
		printf("ENEMY {id=%d dx=%d dy=%d q=%d dist2=%lld member=%d}\n", 
			enemy[enemyId[i]].teamId, enemy[enemyId[i]].dx,
			enemy[enemyId[i]].dy, enemy[enemyId[i]].code,
			enemy[enemyId[i]].dist2,
			enemy[enemyId[i]].member);
	}
	#endif
	
	bool newLine = true;
	for (int i=1; i<=N; ++i) {
		int eid = enemyId[i];
		
		if (newLine) {
			enemy[eid].cost = enemy[eid].member;
			newLine = false;
		} else {
			// encounter new segment
			if (checkInLine(i, i-1)) {
				int barrier = enemyId[i-1];
				enemy[eid].cost = enemy[barrier].cost + enemy[eid].member;
			} else {
				enemy[eid].cost = enemy[eid].member;
			}
		}
	}
	
	for (int i=0; i<Q; ++i) {
		scanf("%d", &ti);
		printf("%lld\n", enemy[ti].cost);
	}
	
	return 0;
}
