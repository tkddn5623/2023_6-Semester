#include <stdio.h>
#define MAXN (500)
inline int arr_idx(int row, int col) {
	return row * (row + 1) / 2 + col;
}
void solve1932_2(int arr[], int N) {
	int max = -1;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j <= i; j++) {
			int a = 0, b = 0;
			if (j > 0) a = arr[arr_idx(i - 1, j - 1)];
			if (j < i) b = arr[arr_idx(i - 1, j)];
			a = a >= b ? a : b;
			arr[arr_idx(i, j)] += a;
		}
	}
	for (int bias = arr_idx(N - 1, 0), i = 0; i < N; i++) 
		max = max < arr[i + bias] ? arr[i + bias] : max;
	printf("%d\n", max);
}
int main() {
	static int arr[MAXN * (MAXN + 1) / 2];
	int N;
	scanf("%d", &N);
	for (int M = N * (N + 1) / 2, i = 0; i < M; i++)
		scanf("%d", &arr[i]);
	solve1932_2(arr, N);
}