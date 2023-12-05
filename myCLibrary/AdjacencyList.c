#include <stdlib.h>
#include "AdjacencyList.h"
/*
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
*/
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

/*
// Dijkstra snippet (2023-11-26)

	struct Pair {
		int id;
		int weight;
	};
    static int distances[MAXN + 1];
    ArrayHeap* heap = AH_new(edgeSize);
	
    for (int j = 1; j <= vtxSize; j++) distances[j] = INF;
    distances[start] = 0;
    AH_push(heap, (struct Pair) { start, 0 }, 0);
    while (!AH_isEmpty(heap)) {
        struct Pair e = AH_pop(heap);
        if (e.weight > distances[e.id]) continue;
        for (GNode* head = &graph->_edges[e.id], *cur = head->next; cur != head; cur = cur->next) {
            int weight = e.weight + cur->weight;
            if (weight < distances[cur->id]) {
                AH_push(heap, (struct Pair) { cur->id, weight }, weight);
                distances[cur->id] = weight;
            }
        }
    }

int _travelingSalesman_impl(Graph* graph, int memo[][1 << MAXVTX], const int vtx, int visited_bit) {
    int dist_min;
    const int vtxsize = graph->vtxsize;
    GNode* const head = &graph->_edges[vtx];
    //if (memo[vtx][visited_bit] != -1) return memo[vtx][visited_bit];
    if (visited_bit == (1 << vtxsize) - 1) {
        for (GNode* cur = head->next; cur != head; cur = cur->next) {
            if (cur->id == HOME) {
                return cur->weight;
            }
        }
        return INF;
    }
    dist_min = INF;
    for (GNode* cur = head->next; cur != head; cur = cur->next) {
        if (visited_bit & (1 << cur->id)) continue;
        const int mem = memo[cur->id][visited_bit | 1 << cur->id];
        int dist = cur->weight;
        if (mem == -1) dist += _travelingSalesman_impl(graph, memo, cur->id, (visited_bit | 1 << cur->id));
        else dist += mem;
        dist_min = dist < dist_min ? dist : dist_min;
    }
    memo[vtx][visited_bit] = dist_min;
    return dist_min;
}
int travelingSalesman(Graph* graph) {
    static int memo[MAXVTX][1 << MAXVTX];
    memset(memo, -1, sizeof(memo));
    return _travelingSalesman_impl(graph, memo, HOME, 1 << HOME);
}

/////////////////////////////////////////////////////////////////////////////

void _Indgree(int* indgree, Graph* graph) {
    int vtxsize = graph->vtxsize;
    int edgecount = graph->edgecount;
    const GNode* _edges = graph->_edges;
    for (int i = vtxsize; i < edgecount; i++) {
        indgree[_edges[i].id]++;
    }
}
void Topological_Sort(int* sorted, Graph* graph) {
    const int vtxmax = graph->vtxsize - 1;
    ArrayQueue* queue = AQ_new(vtxmax + 1);
    int* indgree = calloc(vtxmax + 1, sizeof(int)); if (!indgree) exit(1);
    int sorted_len = 0;
    _Indgree(indgree, graph);
    for (int i = 1; i <= vtxmax; i++) {
        if (indgree[i] > 0) continue;
        AQ_push(queue, i);
    }
    while (!AQ_isEmpty(queue)) {
        int vtx = AQ_pop(queue);
        sorted[sorted_len++] = vtx;
        GNode* head = &graph->_edges[vtx];
        for (GNode* cur = head->next; cur != head; cur = cur->next) {
            if (--indgree[cur->id] > 0) continue;
            AQ_push(queue, cur->id);
        }
    }
    AQ_delete(queue);
    free(indgree);
}
*/

/*
* 2022.9.21 Wed
* 2023.1.6  Fri, improved speed.
* 2023.1.27 Fri, example changed to TSP.
* 2023.7.18 Tue, example add (Topological_Sort)
*/

/*
GNode* const head = graph->tails[vtx]->next; //Slower
GNode* const head = &graph->_edges[vtx];     //Faster (in TSP, difference is small)
*/