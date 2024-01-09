// boj 1182, 1208
// tag: binary search, meet in the middle
#include <stdio.h>
#define MAXN (40)

//#define DEBUG

#ifdef DEBUG
int _answer = -1;
void solve1182(const int seq[], int N, int S) {
	if (N >= 32) return;
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
	_answer = cardinality;
}
#endif // DEBUG

void solve1208(const int seq[], int N, int S) {
	int cardinality = 0;







	printf("%d\n", cardinality);
#ifdef DEBUG
	solve1182(seq, N, S);
	if (cardinality != _answer) {
		printf("You fail (expected %d)\n", _answer);
	}
#endif // DEBUG

}
int main() {
	static int seq[MAXN];
	int N, S;
	scanf("%d%d", &N, &S);
	for (int i = 0; i < N; i++) { scanf("%d", &seq[i]); }
	solve1208(seq, N, S);
}