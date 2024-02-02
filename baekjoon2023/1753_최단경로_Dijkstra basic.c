#include <stdio.h>
#include <stdlib.h>

#define MAXV (20000)
#define INF  (1000000000)

typedef struct {
	int value;
	int priority;
} HNode;

typedef struct _GNode {
	int id;
	int weight;
	struct _GNode* next;
} GNode;

typedef struct {
	HNode* items;
	int size;
} ArrayHeap;

typedef struct {
	int vtxsize;
	int edgesize;
	int edgecount;
	GNode** tails;
	GNode* _edges;
} Graph;


ArrayHeap* AH_new(int max) {
	ArrayHeap* pheap;
	if (!(pheap = calloc(1, sizeof(ArrayHeap)))) exit(1);
	if (!(pheap->items = calloc(max + 1, sizeof(HNode)))) exit(1);
	return pheap;
}
void AH_delete(ArrayHeap* pheap) {
	free(pheap->items);
	free(pheap);
}
int AH_empty(ArrayHeap* pheap) {
	return pheap->size == 0;
}
void AH_push(ArrayHeap* pheap, HNode item) {
	int parent, index = pheap->size + 1;
	while (index > 1) {
		if (item.priority >= pheap->items[(parent = index / 2)].priority) break; // Minheap
		pheap->items[index] = pheap->items[parent];
		index = parent;
	}
	pheap->items[index] = item;
	pheap->size++;
}
HNode AH_pop(ArrayHeap* pheap) {
	const int size = pheap->size;
	const HNode top = pheap->items[1];
	const HNode last = pheap->items[size];
	int child, parent = 1;
	while ((child = parent * 2) <= size) {
		if (child < size && pheap->items[child + 1].priority < pheap->items[child].priority) child++; // Minheap
		if (last.priority <= pheap->items[child].priority) break; // Minheap
		pheap->items[parent] = pheap->items[child];
		parent = child;
	}
	pheap->items[parent] = last;
	pheap->size--;
	return top;
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
void GR_insert(Graph* graph, int from, int to, int weight) {
	graph->_edges[graph->edgecount].id = to;
	graph->_edges[graph->edgecount].weight = weight;
	graph->_edges[graph->edgecount].next = graph->tails[from]->next;
	graph->tails[from]->next = &graph->_edges[graph->edgecount];
	graph->tails[from] = &graph->_edges[graph->edgecount++];
}
void solve1753_dijkstra(int dist[], Graph* graph, int start) {
	for (int j = graph->vtxsize, i = 0; i < j; i++) { dist[i] = INF; }
	dist[start] = 0;

	ArrayHeap* heap = AH_new(graph->edgesize);
	AH_push(heap, (HNode) { start, 0 });

	while (!AH_empty(heap)) {
		HNode e = AH_pop(heap);

		if (e.priority > dist[e.value]) continue;

		for (GNode* head = &graph->_edges[e.value], *cur = head->next; cur != head; cur = cur->next) {
			int weight = e.priority + cur->weight, id = cur->id;
			if (weight < dist[id]) {
				dist[id] = weight;
				AH_push(heap, (HNode) { id, weight });
			}
		}
	}

	AH_delete(heap);
}
int main() {
	//freopen("i.txt", "r", stdin);
	static int dist[MAXV + 1];
	int V, E, S;
	Graph* graph;

	scanf("%d%d%d", &V, &E, &S);
	graph = GR_new(V + 1, E);

	for (int i = 0; i < E; i++) {
		int from, to, weight;
		scanf("%d%d%d", &from, &to, &weight);
		GR_insert(graph, from, to, weight);
	}

	solve1753_dijkstra(dist, graph, S);
	GR_delete(graph);

	for (int i = 1; i <= V; i++) {
		if (dist[i] == INF) printf("INF\n");
		else printf("%d\n", dist[i]);
	}
}