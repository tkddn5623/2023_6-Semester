#include <stdio.h>
#include <stdlib.h>
#define MAXN (100000)

typedef struct {
    int pos;
    int time;
} Nodeinfo;

typedef struct {
    Nodeinfo* items;
    int size;
} ArrayHeap;

ArrayHeap* AH_new(int max) {
    ArrayHeap* pheap;
    if (!(pheap = calloc(1, sizeof(ArrayHeap)))) exit(1);
    if (!(pheap->items = calloc(max + 1, sizeof(Nodeinfo)))) exit(1);
    return pheap;
}
void AH_delete(ArrayHeap* pheap) {
    free(pheap->items);
    free(pheap);
}
int AH_isEmpty(ArrayHeap* pheap) {
    return pheap->size == 0;
}
void AH_push(ArrayHeap* pheap, Nodeinfo item) {
    int index = pheap->size + 1;
    while (index > 1) {
        int parentIndex = index / 2;
        if (item.time < pheap->items[parentIndex].time) {
            // Minheap
            pheap->items[index] = pheap->items[parentIndex];
            index = parentIndex;
        }
        else break;
    }
    pheap->items[index] = item;
    pheap->size++;
}
Nodeinfo AH_pop(ArrayHeap* pheap) {
    const int size = pheap->size;
    const Nodeinfo topitem = pheap->items[1];
    const Nodeinfo last = pheap->items[size];
    int left, pickedChild, parentIndex = 1;
    while ((left = parentIndex * 2) <= size) {
        if (left == size || pheap->items[left].time < pheap->items[left + 1].time) pickedChild = left;
        // Minheap
        else pickedChild = left + 1;
        if (last.time > pheap->items[pickedChild].time) {
            // Minheap
            pheap->items[parentIndex] = pheap->items[pickedChild];
            parentIndex = pickedChild;
        }
        else break;
    }
    pheap->items[parentIndex] = last;
    pheap->size--;
    return topitem;
}

void solve13549(int N, int K) {
    static int visited[MAXN];
    int states = -1;
    ArrayHeap* heap = AH_new(70000);

    AH_push(heap, (Nodeinfo) { N, 1 });

    while (!AH_isEmpty(heap)) {
        Nodeinfo node = AH_pop(heap);

        if (node.pos == K) { states = node.time - 1; break; }
        if (visited[node.pos] && visited[node.pos] <= node.time) continue;

        visited[node.pos] = node.time;

        if (node.pos * 2 <= 100000) AH_push(heap, (Nodeinfo) { node.pos * 2, node.time });
        if (node.pos - 1 >= 0) AH_push(heap, (Nodeinfo) { node.pos - 1, node.time + 1 });
        if (node.pos + 1 <= 100000) AH_push(heap, (Nodeinfo) { node.pos + 1, node.time + 1 });
    }

    AH_delete(heap);
    printf("%d\n", states);
}
int main() {
    int N, K;
    scanf("%d%d", &N, &K);
    solve13549(N, K);
}