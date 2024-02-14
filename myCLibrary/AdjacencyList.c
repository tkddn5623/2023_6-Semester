#include <stdlib.h>

typedef struct _GNode {
	union { struct { int id, weight; }; struct _GNode* tail; };
	struct _GNode* next;
} GNode;

typedef struct {
	GNode* edges;
	int vtxsize;
	int edgesize;
	int edgecount;
} Graph;

Graph* GR_new(int vtxsize, int edgesize) {
	Graph* graph;
	graph = malloc(sizeof(Graph)); if (!graph) exit(1);
	graph->edges = calloc(edgesize + vtxsize, sizeof(GNode)) if (!graph->edges) exit(1);
	graph->vtxsize = vtxsize;
	graph->edgesize = edgesize + vtxsize;
	graph->edgecount = vtxsize;
	for (int i = 0; i < vtxsize; i++) {
		graph->edges[i].next = &graph->edges[i];
		graph->edges[i].tail = &graph->edges[i];
	}
	return graph;
}
void GR_delete(Graph* graph) {
	free(graph->edges);
	free(graph);
}
void GR_insert(Graph* graph, int from, int to, int weight) {
	graph->edges[graph->edgecount] = (GNode){ .id = to, .weight = weight, .next = &graph->edges[from] };
	graph->edges[from].tail->next = &graph->edges[graph->edgecount];
	graph->edges[from].tail = &graph->edges[graph->edgecount++];
}

/////////// Dijkstra, Prim snippet (2024.01.27) /////////////////////////////////////

/*
#define INF  (1000000000)
typedef struct {
    int value;
    int priority;
} HNode;
*/

void solve1753_Dijkstra(int dist[], const Graph* graph, int start) {
    for (int j = graph->vtxsize, i = 0; i < j; i++) { dist[i] = INF; }
    dist[start] = 0;

    ArrayHeap* heap = AH_new(graph->edgesize);
    AH_push(heap, (HNode) { start, 0 });

    while (!AH_empty(heap)) {
        HNode e = AH_pop(heap);

        if (e.priority > dist[e.value]) continue;

        for (GNode* head = &graph->edges[e.value], *cur = head->next; cur != head; cur = cur->next) {
            int weight = e.priority + cur->weight, id = cur->id;
            if (weight < dist[id]) {
                dist[id] = weight;
                AH_push(heap, (HNode) { id, weight });
            }
        }
    }

    AH_delete(heap);
}

void solve1197_Prim(const Graph* graph) {
	static int dist[MAXV + 1];
	static int visited[MAXV + 1];
	int mst_length = 0;

	for (int j = graph->vtxsize, i = 1; i < j; i++) { dist[i] = INF; /*visited[i] = 0;*/ }
	dist[1] = 0;

	ArrayHeap* heap = AH_new(graph->edgesize);
	AH_push(heap, (HNode) { 1, 0 });
	
	while (!AH_empty(heap)) {
		HNode e = AH_pop(heap);
		
		if (visited[e.value]) continue;

		visited[e.value] = 1;
		mst_length += e.priority;

		for (GNode* head = &graph->edges[e.value], *cur = head->next; cur != head; cur = cur->next) {
			int weight = cur->weight, id = cur->id;
			if (!visited[id] && weight < dist[id]) {
				dist[id] = weight;
				AH_push(heap, (HNode) { id, weight });
			}
		}
	}

	AH_delete(heap);
	printf("%d\n", mst_length);
}

/////////// Bellman Ford snippet (2024.01.29) ///////////////////////////////////////

void solve11657_Bellman_Ford(long long dist[], const Graph* graph, int start) {
	const int vtxmax = graph->vtxsize - 1;

	// Assume there is no vertex 0.
	for (int i = 1; i <= vtxmax; i++) { dist[i] = INF; }
	dist[start] = 0;

	// A loop of (vtxmax - 1) is enough to propagate.
	for (int i = 0; i < vtxmax - 1; i++) for (int j = 1; j <= vtxmax; j++) {
		for (GNode* head = &graph->edges[j], *cur = head->next; cur != head; cur = cur->next) {
			int weight = cur->weight, id = cur->id;
			if (dist[j] == INF || dist[id] <= dist[j] + weight) continue;
			dist[id] = dist[j] + weight;
		}
	}

	// Minus cycle check
	for (int j = 1; j <= vtxmax; j++) {
		for (GNode* head = &graph->edges[j], *cur = head->next; cur != head; cur = cur->next) {
			int weight = cur->weight, id = cur->id;
			if (dist[j] == INF || dist[id] <= dist[j] + weight) continue;
			dist[0] = -INF;
			goto LOOPOUT;
		}
	} LOOPOUT:;
}

/////////// Floyd_Warshall snippet (not adj list) (2024.01.29) //////////////////////

void solve11404_Floyd_Warshall(int dist[][MAXV + 1], int vtxmax) {
	for (int k = 1; k <= vtxmax; k++) for (int i = 1; i <= vtxmax; i++) for (int j = 1; j <= vtxmax; j++) {
		dist[i][j] = Min(dist[i][j], dist[i][k] + dist[k][j]);
	}
}

/////////////////////////////////////////////////////////////////////////////////////

int _travelingSalesman_impl(const Graph* graph, int memo[][1 << MAXVTX], const int vtx, int visited_bit) {
    int dist_min;
    const int vtxsize = graph->vtxsize;
    GNode* const head = &graph->edges[vtx];
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

/////// Topological Sort Snippet (2024.1.29) ////////////////////////////////////////

void _Topological_Sort_Indgree(int indgree[], const Graph* graph) {
	int vtxsize = graph->vtxsize;
	int edgecount = graph->edgecount;
	const GNode* edges = graph->edges;
	for (int i = vtxsize; i < edgecount; i++) {
		indgree[edges[i].id]++;
	}
}
void Topological_Sort(int sorted[], const Graph* graph) {
	const int vtxmax = graph->vtxsize - 1;
	int sorted_len = 0;
	int* indgree;

	if (!(indgree = calloc(vtxmax + 1, sizeof(int)))) exit(1);
	ArrayQueue* queue = AQ_new(vtxmax + 1);
	_Topological_Sort_Indgree(indgree, graph);

	for (int i = 1; i <= vtxmax; i++) {
		if (indgree[i] > 0) continue;
		AQ_push(queue, i);
	}

	while (!AQ_empty(queue)) {
		int vtx = AQ_pop(queue);
		sorted[sorted_len++] = vtx;
		for (GNode* head = &graph->edges[vtx], *cur = head->next; cur != head; cur = cur->next) {
			if (--indgree[cur->id] > 0) continue;
			AQ_push(queue, cur->id);
		}
	}

	AQ_delete(queue);
	free(indgree);
}


/*
* 2022.9.21 Wed
* 2023.1.6  Fri, improved speed.
* 2023.1.27 Fri, example changed to TSP.
* 2023.7.18 Tue, example add (Topological_Sort)
* 2024.1.22 Mon, change to snake cases
* 2024.1.29 Mon, examples renewal
* 2024.2.12 Mon, Using union to represent tail: save more memory space
*/

/*
GNode* const head = graph->tails[vtx]->next; //Slower
GNode* const head = &graph->edges[vtx];     //Faster (in TSP, difference is small)
*/