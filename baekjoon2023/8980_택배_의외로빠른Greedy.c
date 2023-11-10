#include <stdio.h>
#include <stdlib.h>
#define MAXM (10000)
#define MAXN (2000)
struct node {
	int from;
	int to;
	int value;
};
inline int _cmp(struct node a, struct node b) {
	if (a.to > b.to) return 1;
	else if (a.to < b.to || a.from > b.from) return -1;
	else if (a.from < b.from) return 1;
	else return 0;
}
void _MergeSort_impl(struct node* list, struct node* sorted, const int left, const int right) {
	if (left >= right) return;
	const int mid = left + (right - left) / 2;
	_MergeSort_impl(list, sorted, left, mid);
	_MergeSort_impl(list, sorted, mid + 1, right);
	int idx, first, second;
	idx = left, first = left, second = mid + 1;
	while (first <= mid && second <= right) {
		if (_cmp(list[first], list[second]) < 1) sorted[idx++] = list[first++];
		else sorted[idx++] = list[second++];
	}
	while (first <= mid)    sorted[idx++] = list[first++];
	while (second <= right) sorted[idx++] = list[second++];
	for (int i = left; i <= right; i++) list[i] = sorted[i];
}
void MergeSort(struct node* list, int size) {
	static struct node sorted[MAXM];
	_MergeSort_impl(list, sorted, 0, size - 1);
}
void solve8980(struct node boxes[], int N, int C, int M) {
	static int C_used[MAXN + 1];
	int C_used_max, answer;
	
	MergeSort(boxes, M);
	answer = 0;
	for (int i = 0; i < M; i++) {
		register struct node B = boxes[i];
		//if (B.to < 0 || B.to >= MAXN + 1) exit(1); // Buffer overrun
		
		C_used_max = C_used[B.from];
		for (int i = B.from + 1; i <= B.to; i++) {
			if (C_used_max < C_used[i]) C_used_max = C_used[i];
			if (C_used_max == C) break;
		}

		if (C_used_max == C) continue;
		else if (C_used_max + B.value <= C) {
			answer += B.value;
			for (int i = B.from; i < B.to; i++) {
				C_used[i] += B.value;
			}
		}
		else {
			answer += C - C_used_max;
			for (int i = B.from; i < B.to; i++) {
				C_used[i] += C - C_used_max;
			}
		}
	}
	printf("%d\n", answer);
}
int main() {
	static struct node boxes[MAXM];
	int N, C, M;
	scanf("%d%d%d", &N, &C, &M);
	for (int i = 0; i < M; i++) {
		scanf("%d%d%d", &boxes[i].from, &boxes[i].to, &boxes[i].value);
	}
	solve8980(boxes, N, C, M);
}