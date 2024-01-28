#include <stdio.h>

#define MAXV (100)
#define INF (500000000)

int Min(const int a, const int b) {
	return a <= b ? a : b;
}
void solve11404_Floyd_Warshall(int dist[][MAXV + 1], int vtxmax) {
	for (int k = 1; k <= vtxmax; k++) for (int i = 1; i <= vtxmax; i++) for (int j = 1; j <= vtxmax; j++) {
		dist[i][j] = Min(dist[i][j], dist[i][k] + dist[k][j]);
	}
}
int main() {
	// freopen("i.txt", "r", stdin);
	static int dist[MAXV + 1][MAXV + 1];
	int V, E;
	scanf("%d%d", &V, &E);

	for (int i = 1; i <= V; i++) for (int j = 1; j <= V; j++) {
		dist[i][j] = i == j ? 0 : INF;
	}

	for (int i = 0; i < E; i++) {
		int from, to, weight;
		scanf("%d%d%d", &from, &to, &weight);
		dist[from][to] = Min(dist[from][to], weight);
	}

	solve11404_Floyd_Warshall(dist, V);

	for (int i = 1; i <= V; i++) {
		for (int j = 1; j <= V; j++) { printf("%d ", dist[i][j] == INF ? 0 : dist[i][j]); }
		printf("\n");
	}
}