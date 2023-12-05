#include <stdio.h>
#include <stdlib.h>
#define INF (10000000)
#define MAXN (1000)
typedef struct {
	struct Pair {
		int id;
		int weight;
	} item;
	int priority;
} HNode;
typedef struct {
	HNode* nodes;
	int size;
} ArrayHeap;
typedef struct _GNode {
	int id;
	int weight;
	struct _GNode* next;
} GNode;
typedef struct {
	int vtxsize;
	int edgesize;
	int edgecount;
	GNode** tails;
	GNode* _edges;
} Graph;
ArrayHeap* AH_new(int max) {
	ArrayHeap* pheap;
	if ((pheap = calloc(1, sizeof(ArrayHeap))) == NULL) exit(1);
	if ((pheap->nodes = calloc(max + 1, sizeof(HNode))) == NULL) exit(1);
	return pheap;
}
void AH_flush(ArrayHeap* pheap) {
	pheap->size = 0;
}
void AH_delete(ArrayHeap* pheap) {
	free(pheap->nodes);
	free(pheap);
}
int AH_isEmpty(ArrayHeap* pheap) {
	return pheap->size == 0;
}
void AH_push(ArrayHeap* pheap, struct Pair item, int priority) {
	HNode newNode;
	int index = pheap->size + 1;
	while (index > 1) {
		int parentIndex = index / 2;
		if (priority < pheap->nodes[parentIndex].priority) {
			//Minheap
			pheap->nodes[index] = pheap->nodes[parentIndex];
			index = parentIndex;
		}
		else break;
	}
	newNode.item.id = item.id;
	newNode.item.weight = item.weight;
	newNode.priority = priority;
	pheap->nodes[index] = newNode;
	pheap->size++;
}
struct Pair AH_pop(ArrayHeap* pheap) {
	const int size = pheap->size;
	const struct Pair topitem = pheap->nodes[1].item;
	const HNode last = pheap->nodes[size];
	int left, pickedChild, parentIndex = 1;
	while ((left = parentIndex * 2) <= size) {
		if (left == size) pickedChild = left;
		else if (pheap->nodes[left].priority < pheap->nodes[left + 1].priority) pickedChild = left;
		//Minheap
		else pickedChild = left + 1;
		if (last.priority > pheap->nodes[pickedChild].priority) {
			//Minheap
			pheap->nodes[parentIndex] = pheap->nodes[pickedChild];
			parentIndex = pickedChild;
		}
		else break;
	}
	pheap->nodes[parentIndex] = last;
	pheap->size--;
	return topitem;
}
Graph* GR_new(int vtxsize, int edgesize) {
	Graph* graph;
	if ((graph = malloc(sizeof(Graph))) == NULL) exit(1);
	if ((graph->tails = calloc(vtxsize, sizeof(GNode*))) == NULL) exit(1);
	if ((graph->_edges = calloc(edgesize + vtxsize, sizeof(GNode))) == NULL) exit(1);
	graph->vtxsize = vtxsize;
	graph->edgesize = edgesize + vtxsize;
	graph->edgecount = vtxsize;
	for (int i = 0; i < vtxsize; i++) {
		graph->tails[i] = &graph->_edges[i];
		graph->tails[i]->next = graph->tails[i];
	}
	return graph;
}
void GR_delete(Graph* graph) {
	free(graph->_edges);
	free(graph->tails);
	free(graph);
}
void GR_addEdge(Graph* graph, int from, int to, int weight) {
	graph->_edges[graph->edgecount].id = to;
	graph->_edges[graph->edgecount].weight = weight;
	graph->_edges[graph->edgecount].next = graph->tails[from]->next;
	graph->tails[from]->next = &graph->_edges[graph->edgecount];
	graph->tails[from] = &graph->_edges[graph->edgecount++];
}
void solve1208(Graph* graph, int N, int M, int X) {
	static int distances1[MAXN + 1];
	static int distances2[MAXN + 1];
	ArrayHeap* heap = AH_new(M);
	int answer = -1;

	// Make X -> i distances
	do {
		for (int j = 1; j <= N; j++) distances1[j] = INF;
		distances1[X] = 0;
		AH_push(heap, (struct Pair) { X, 0 }, 0);
		while (!AH_isEmpty(heap)) {
			struct Pair e = AH_pop(heap);
			if (e.weight > distances1[e.id]) continue;
			for (GNode* head = &graph->_edges[e.id], *cur = head->next; cur != head; cur = cur->next) {
				int weight = e.weight + cur->weight;
				if (weight < distances1[cur->id]) {
					AH_push(heap, (struct Pair) { cur->id, weight }, weight);
					distances1[cur->id] = weight;
				}
			}
		}
	} while (0);

	// Make i -> X distances
	for (int i = 1; i <= N; i++) {
		if (i == X) continue;
		for (int j = 1; j <= N; j++) distances2[j] = INF;
		distances2[i] = 0;
		AH_flush(heap);
		AH_push(heap, (struct Pair) { i, 0 }, 0);
		while (!AH_isEmpty(heap)) {
			struct Pair e = AH_pop(heap);
			if (e.weight > distances2[e.id]) continue;
			for (GNode* head = &graph->_edges[e.id], *cur = head->next; cur != head; cur = cur->next) {
				int weight = e.weight + cur->weight;
				if (weight < distances2[cur->id]) {
					AH_push(heap, (struct Pair) { cur->id, weight }, weight);
					distances2[cur->id] = weight;
				}
			}
		}
		if (answer < distances1[i] + distances2[X]) answer = distances1[i] + distances2[X];
	}
	AH_delete(heap);
	printf("%d\n", answer);
}
int main() {
	Graph* graph;
	int N, M, X;
	scanf("%d%d%d", &N, &M, &X);
	graph = GR_new(N + 1, M);
	for (int i = 0; i < M; i++) {
		int from, to, time;
		scanf("%d%d%d", &from, &to, &time);
		GR_addEdge(graph, from, to, time);
	}
	solve1208(graph, N, M, X);
	GR_delete(graph);
}