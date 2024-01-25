#include <stdio.h>
#include <stdlib.h>

#define MAXM (9999)

typedef struct {
	int* items;
	int size;
} ArrayHeap;

ArrayHeap* AH_new(int max) {
	ArrayHeap* pheap;
	if (!(pheap = calloc(1, sizeof(ArrayHeap)))) exit(1);
	if (!(pheap->items = calloc(max + 1, sizeof(int)))) exit(1);
	return pheap;
}
void AH_delete(ArrayHeap* pheap) {
	free(pheap->items);
	free(pheap);
}
void AH_push_min(ArrayHeap* pheap, int item) {
	int index = pheap->size + 1;
	while (index > 1) {
		int parentIndex = index / 2;
		if (item < pheap->items[parentIndex]) {
			//Minheap
			pheap->items[index] = pheap->items[parentIndex];
			index = parentIndex;
		}
		else break;
	}
	pheap->items[index] = item;
	pheap->size++;
}
int AH_pop_min(ArrayHeap* pheap) {
	const int size = pheap->size;
	const int topitem = pheap->items[1];
	const int last = pheap->items[size];
	int left, pickedChild, parentIndex = 1;
	while ((left = parentIndex * 2) <= size) {
		if (left == size || pheap->items[left] < pheap->items[left + 1]) pickedChild = left;
		//Minheap
		else pickedChild = left + 1;
		if (last > pheap->items[pickedChild]) {
			//Minheap
			pheap->items[parentIndex] = pheap->items[pickedChild];
			parentIndex = pickedChild;
		}
		else break;
	}
	pheap->items[parentIndex] = last;
	pheap->size--;
	return topitem;
}
void AH_push_max(ArrayHeap* pheap, int item) {
	int index = pheap->size + 1;
	while (index > 1) {
		int parentIndex = index / 2;
		if (item > pheap->items[parentIndex]) {
			//Maxheap
			pheap->items[index] = pheap->items[parentIndex];
			index = parentIndex;
		}
		else break;
	}
	pheap->items[index] = item;
	pheap->size++;
}
int AH_pop_max(ArrayHeap* pheap) {
	const int size = pheap->size;
	const int topitem = pheap->items[1];
	const int last = pheap->items[size];
	int left, pickedChild, parentIndex = 1;
	while ((left = parentIndex * 2) <= size) {
		if (left == size || pheap->items[left] > pheap->items[left + 1]) pickedChild = left;
		//Maxheap
		else pickedChild = left + 1;
		if (last < pheap->items[pickedChild]) {
			//Maxheap
			pheap->items[parentIndex] = pheap->items[pickedChild];
			parentIndex = pickedChild;
		}
		else break;
	}
	pheap->items[parentIndex] = last;
	pheap->size--;
	return topitem;
}
void AH_flush(ArrayHeap* pheap) {
	pheap->size = 0;
}
void solve2696(ArrayHeap* heap_left, ArrayHeap* heap_right, int M) {
	int a, b, mid;

	AH_flush(heap_left);
	AH_flush(heap_right);

	scanf("%d", &mid);

	printf("%d\n%d", M / 2 + 1, mid);

	for (int j = M / 2, i = 0; i < j; i++) {
		int c;

		scanf("%d%d", &a, &b);

		if (a > b) {
			int temp = a;
			a = b;
			b = temp;
		}

		if (a >= mid && b >= mid) {
			AH_push_min(heap_right, a);
			AH_push_min(heap_right, b);
			c = AH_pop_min(heap_right);
			AH_push_max(heap_left, mid);
			mid = c;
		}
		else if (a <= mid && b <= mid) {
			AH_push_max(heap_left, a);
			AH_push_max(heap_left, b);
			c = AH_pop_max(heap_left);
			AH_push_min(heap_right, mid);
			mid = c;
		}
		else {
			AH_push_max(heap_left, a);
			AH_push_min(heap_right, b);
		}

		printf("%c%d", i % 10 == 9 ? '\n' : ' ', mid);
	}
	putchar('\n');
}
int main() {
	int T;
	ArrayHeap* heap_left = AH_new(MAXM);
	ArrayHeap* heap_right = AH_new(MAXM);

	scanf("%d", &T);

	do {
		int M;
		scanf("%d", &M);
		solve2696(heap_left, heap_right, M);
	} while (--T > 0);

	AH_delete(heap_left);
	AH_delete(heap_right);
}