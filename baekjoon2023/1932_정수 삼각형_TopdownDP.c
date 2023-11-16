#include <stdio.h>
#define MAXN (500)
static int memo[MAXN * (MAXN + 1) / 2];

inline int arr_idx(int row, int col) {
	return row * (row + 1) / 2 + col;
}
int _solve1932_impl(int arr[], int row, int col, int value) {
	int idx, a, b;
	if (memo[idx = arr_idx(row, col)]) return memo[idx];
	a = 0, b = 0;
	if (col > 0)	a = _solve1932_impl(arr, row - 1, col - 1, value);
	if (col < row)	b = _solve1932_impl(arr, row - 1, col, value);
	a = a >= b ? a : b;
	return memo[idx] = a + arr[idx];
}
void solve1932(int arr[], int N) {
	int max = -1;
	for (int i = 0; i < N; i++) {
		int a = _solve1932_impl(arr, N - 1, i, 0);
		max = a > max ? a : max;
	}
	printf("%d\n", max);
}
int main() {
	static int arr[MAXN * (MAXN + 1) / 2];
	int N;
	scanf("%d", &N);
	for (int M = N * (N + 1) / 2, i = 0; i < M; i++) 
		scanf("%d", &arr[i]);
	solve1932(arr, N);
}