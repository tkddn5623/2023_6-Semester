#include <stdio.h>
#include <stdlib.h>

#define MAXV (500)
#define INF  (1000000000)

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
void solve11657_Bellman_Ford(long long dist[], Graph* graph, int start) {
	const int vtxmax = graph->vtxsize - 1;

	// Assume there is no vertex 0.
	for (int i = 1; i <= vtxmax; i++) { dist[i] = INF; }
	dist[start] = 0;

	// A loop of (vtxmax - 1) is enough to propagate.
	for (int i = 0; i < vtxmax - 1; i++) for (int j = 1; j <= vtxmax; j++) {
		for (GNode* head = &graph->_edges[j], *cur = head->next; cur != head; cur = cur->next) {
			int weight = cur->weight, id = cur->id;
			if (dist[j] == INF || dist[id] <= dist[j] + weight) continue;
			dist[id] = dist[j] + weight;
		}
	}

	// Minus cycle check
	for (int j = 1; j <= vtxmax; j++) {
		for (GNode* head = &graph->_edges[j], *cur = head->next; cur != head; cur = cur->next) {
			int weight = cur->weight, id = cur->id;
			if (dist[j] == INF || dist[id] <= dist[j] + weight) continue;
			dist[0] = -INF;
			goto LOOPOUT;
		}
	} LOOPOUT:;

}
int main() {
	// freopen("i.txt", "r", stdin);
	static long long dist[MAXV + 1];
	int V, E;
	Graph* graph;

	scanf("%d%d", &V, &E);
	graph = GR_new(V + 1, E);

	for (int i = 0; i < E; i++) {
		int from, to, weight;
		scanf("%d%d%d", &from, &to, &weight);
		GR_insert(graph, from, to, weight);
	}

	solve11657_Bellman_Ford(dist, graph, 1);
	GR_delete(graph);

	if (dist[0] == -INF) {
		printf("-1\n");
	}
	else {
		for (int i = 2; i <= V; i++) {
			printf("%lld\n", dist[i] == INF ? -1 : dist[i]);
		}
	}
}