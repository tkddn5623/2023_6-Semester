// boj 1182, 1208
#include <stdio.h>
#define MAXN (20)
void solve1182(const int seq[], int N, int S) {
	int cardinality = 0;
	const int mask_max = (0x1 << N) - 1;
	for (int mask = 0x1; mask <= mask_max; mask++) {
		int sum = 0;
		for (int i = 0; i < N; i++) {
			if (!(mask & (0x1 << i))) continue;
			sum += seq[i];
		}
		if (sum == S) cardinality++;
	}
	printf("%d\n", cardinality);
}
int main() {
	static int seq[MAXN];
	int N, S;
	scanf("%d%d", &N, &S);
	for (int i = 0; i < N; i++) { scanf("%d", &seq[i]); }
	solve1182(seq, N, S);
}