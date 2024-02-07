#define __USE_MINGW_ANSI_STDIO 0
#include <stdio.h>

#define MAXN (200000)

typedef struct {
	int idx1;
	int idx2;
	int size;
} QNode;

void SG_construct(QNode _Dest[], const int items[], const int item_len) {
	int leafs = 1;
	while (leafs < item_len) { leafs <<= 1; }
	for (int i = 0; i < item_len; i++) {
		_Dest[i + leafs].idx1 = i;
		_Dest[i + leafs].size = 1;

	}
	for (int i = item_len; i < leafs; i++) {
		_Dest[i + leafs].size = 0;
	}
	for (int i = leafs - 1; i >= 1; i--) {
		if (_Dest[i * 2].size == 2) {
			_Dest[i] = _Dest[i * 2];
		}
		else if (_Dest[i * 2 + 1].size == 2) {
			_Dest[i] = _Dest[i * 2 + 1];
		}
		else {
			int idx_arr[2] = { -1, -1 };
			int idx_arr_size = 0;

			if (_Dest[i * 2].size == 1) idx_arr[idx_arr_size++] = _Dest[i * 2].idx1;
			if (_Dest[i * 2 + 1].size == 1) idx_arr[idx_arr_size++] = _Dest[i * 2 + 1].idx1;

			if (idx_arr_size == 2 && items[idx_arr[0]] != items[idx_arr[1]]) {
				/*if (idx_arr[0] > idx_arr[1]) {
					int temp = idx_arr[0];
					idx_arr[0] = idx_arr[1];
					idx_arr[1] = temp;
				}*/

				_Dest[i] = (QNode){ idx_arr[0], idx_arr[1], 2 };
			}
			else if (idx_arr_size > 0) {
				_Dest[i].idx1 = idx_arr[0];
				_Dest[i].size = 1;
			}
			else {
				_Dest[i].size = 0;
			}
		}
		//_Dest[i] = _Dest[i * 2] + _Dest[i * 2 + 1];
	}
	_Dest[0].idx1 = leafs;
}
int solve_round923_D_query(const QNode segtree[], const int items[], int from, int to) {
	int answer[4] = { -1,-1,-1,-1 };
	int answer_len = 0;
	from += segtree[0].idx1; to += segtree[0].idx1;
	while (from <= to && answer_len < 2) {
		//printf("current f, t (%d, %d)\n", from, to);
		if (from % 2 == 1) {
			if (segtree[from].size >= 1) {
				if (answer[0] == -1 || items[answer[0]] != items[segtree[from].idx1])
					answer[answer_len++] = segtree[from].idx1;
			}
			if (segtree[from].size >= 2) {
				if (answer[0] == -1 || items[answer[0]] != items[segtree[from].idx2])
					answer[answer_len++] = segtree[from].idx2;
			}
			from++;
			//printf("Now from: %d\n", from);
		}
		if (to % 2 == 0) {
			if (segtree[to].size >= 1) {
				if (answer[0] == -1 || items[answer[0]] != items[segtree[to].idx1])
					answer[answer_len++] = segtree[to].idx1;
			}
			if (segtree[to].size >= 2) {
				if (answer[0] == -1 || items[answer[0]] != items[segtree[to].idx2])
					answer[answer_len++] = segtree[to].idx2;
			}
			to--;
			//printf("Now to: %d\n", to);
			
		}
		from /= 2; to /= 2;
	}
	if (answer_len < 2) printf("-1 -1\n");
	else printf("%d %d\n", answer[0] + 1, answer[1] + 1);
}
void solve_round923_D_setup(QNode segtree[], int nums[], int N) {
	SG_construct(segtree, nums, N);
}
int main() {
	//freopen("i.txt", "r", stdin);
	static int nums[MAXN];
	static QNode segtree[1 << 19];
	int T;
	scanf("%d", &T);
	do {
		int N, Q;
		scanf("%d", &N);
		for (int i = 0; i < N; i++) {
			scanf("%d", &nums[i]);
		}
		solve_round923_D_setup(segtree, nums, N);
		scanf("%d", &Q);
		for (int i = 0; i < Q; i++) {
			int from, to;
			scanf("%d%d", &from, &to);
			solve_round923_D_query(segtree, nums, from - 1, to - 1);
		}
		putchar('\n');
	} while (--T > 0);
}