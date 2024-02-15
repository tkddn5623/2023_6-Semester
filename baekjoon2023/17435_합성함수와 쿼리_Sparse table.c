#include <stdio.h>

#define MAXM (200000)
#define MAXLOG (19)

void solve17435_setup(int sparse_table[][MAXLOG], int M) {
	// The value of moving 8 times is obtained by moving 4 times twice.
	for (int i = 1; i < MAXLOG; i++) for (int j = 1; j <= M; j++) {
		sparse_table[j][i] = sparse_table[sparse_table[j][i - 1]][i - 1];
	}
}
void solve17435_query(int sparse_table[][MAXLOG], int M, int x, int n) {
	for (int i = 0; i < MAXLOG; i++) {
		if (n & (1 << i)) x = sparse_table[x][i];
	}
	printf("%d\n", x);
}
int main() {
	//freopen("i.txt", "r", stdin);
	static int sparse_table[MAXM + 1][MAXLOG];
	int M, Q;

	scanf("%d", &M);

	for (int i = 1; i <= M; i++) {
		scanf("%d", &sparse_table[i][0]);
	}

	scanf("%d", &Q);
	solve17435_setup(sparse_table, M);

	for (int i = 0; i < Q; i++) {
		int n, x;
		scanf("%d%d", &n, &x);
		solve17435_query(sparse_table, M, x, n);
	}
	
}