#include <stdio.h>
#include <stdlib.h>

#define HASH_MSB_BITS (18)
#define HASH_BLOCK_SIZE (1 << HASH_MSB_BITS)

typedef int Element;

typedef struct _HNode {
	Element item;
	struct _HNode* next;
} HNode;

typedef struct {
	int blocksize;
	int nodesize;
	int nodecount;
	HNode** tails;
	HNode* _edges;
} Hashtable;


int tiny_hash_i32(unsigned int k) {
	return (k * 2654435769u) >> (32 - HASH_MSB_BITS);
}
int tiny_hash_i64(unsigned long long k) {
	return (k * 11400714819323198485llu) >> (64 - HASH_MSB_BITS);
}
Hashtable* HT_new(int blocksize, int nodesize) {
	Hashtable* table;
	if (!(table = malloc(sizeof(Hashtable)))) exit(1);
	if (!(table->tails = calloc(blocksize, sizeof(HNode*)))) exit(1);
	if (!(table->_edges = calloc(nodesize + blocksize, sizeof(HNode)))) exit(1);
	table->blocksize = blocksize;
	table->nodesize = nodesize + blocksize;
	table->nodecount = blocksize;
	for (int i = 0; i < blocksize; i++) {
		table->tails[i] = &table->_edges[i];
		table->tails[i]->next = table->tails[i];
	}
	return table;
}
void HT_delete(Hashtable* table) {
	free(table->_edges);
	free(table->tails);
	free(table);
}
void HT_push(Hashtable* table, Element item) {
	int index = tiny_hash_i32(item);
	table->_edges[table->nodecount].item = item;
	table->_edges[table->nodecount].next = table->tails[index]->next;
	table->tails[index]->next = &table->_edges[table->nodecount];
	table->tails[index] = &table->_edges[table->nodecount++];
}
int HT_search(const Hashtable* table, Element item) {
	int index = tiny_hash_i32(item);
	HNode* head = &table->_edges[index];
	for (HNode* cur = head->next; cur != head; cur = cur->next) {
		if (cur->item == item) return 1;
	}
	return 0;
}

#define HASH1

int main() {
	static int arr[HASH_BLOCK_SIZE];
	static int count[50];
	static int mvcount[1000000];
	int count_total = 0;
	int mvcount_total = 0;

	int k = HASH_BLOCK_SIZE * 65 / 100;
	printf("[K(%d) / BLSZ(%d)]\n", k, HASH_BLOCK_SIZE);

	for (int i = 0; i < k; i++) {
		int num = (i - HASH_BLOCK_SIZE / 2);
		//int num = i;
		int hash = tiny_hash_i64(num);
#ifdef HASH1
		if (arr[hash] >= 1) {
			for (int j = 1; j < HASH_BLOCK_SIZE; j++) {
				int next = (hash + j) % HASH_BLOCK_SIZE;
				//printf("Hash (%d -> %d)\n", hash, next);
				if (arr[next] == 0) {
					//printf("Put it on %d!\n", j);
					if (j >= 10) {
						//printf("Too Heavy...[mov %d] [hash: %d] (%d / %d)\n", j, next, i, k);
						;
					}
					if (j < 1000000) {
						mvcount[j]++;
					}
					arr[next]++;
					break;
				}
			}
		}
		else {
			mvcount[0]++;
			arr[hash]++;
		}
#endif
#ifndef HASH1
		arr[hash]++;
#endif
	}

	for (int j = 0, i = 0; i < HASH_BLOCK_SIZE; i++) {
		//if (arr[i] == 0) continue;
		count[arr[i]]++;
		//printf("(%d th) arr[%d] => %d\n", j++, i, arr[i]);
		
		/*
		if (arr[i] >= 2) printf("(%3d, %3d) --- --- --- ---\n", i, arr[i]);
		if (arr[i] >= 1) printf("(%3d, %3d) --- ---\n", i, arr[i]);
		else             printf("(%3d,   0) \n", i);
		*/
	}

	long long refavg = 0;

	for (int i = 0; i < 50; i++) {
		if (count[i] == 0) continue;
		printf("Cnt (%d) => %d\n", i, count[i]);
		count_total += count[i];
		if (i > 0) {
			refavg += (long long)count[i] * i * (i + 1) / 2;
		}

	}
	printf("\nCnt sum: %d\n\n", count_total);
	printf("Cnt ref avg: %f\n\n", (double)refavg / (count_total - count[0]));

#ifdef HASH1
	long long mvavg = 0;

	for (int i = 0; i < 1000000; i++) {
		if (mvcount[i] == 0) continue;
		printf("Mov (%d) => %d\n", i, mvcount[i]);
		mvavg += (long long)i * mvcount[i];
		mvcount_total += mvcount[i];
	}
	printf("\nMov sum: %d\n\n", mvcount_total);
	printf("\nMovavg sum: %f\n\n", (double)mvavg / mvcount_total);

	int start = -1;
	for (int i = 0; i < HASH_BLOCK_SIZE; i++) {
		if (arr[i] == 0 && arr[(i + 1) % HASH_BLOCK_SIZE] != 0) start = (i + 1) % HASH_BLOCK_SIZE;
	}
	printf("\nStart from hashidx %d\n", start);
	if (start == -1) {
		printf("All blocks connected.\n");
		exit(1);
	}

#define LENMAX (1000000)
	static int lencount[LENMAX];
	int len = 0;
	for (int i = 0; i < HASH_BLOCK_SIZE; i++) {
		if (arr[(start + i) % HASH_BLOCK_SIZE] == 0) {
			if (len > 0 && len < LENMAX) {
				lencount[len]++;
			}
			if (len > HASH_BLOCK_SIZE / 1000 && len > 20) {
				printf("!!!Super big chunk detected\n");
			}
			lencount[0]++;
			len = 0;
		}
		else {
			len++;
		}
	}

	for (int i = 0; i < LENMAX; i++) {
		if (lencount[i] == 0) {
			continue;
		}
		printf("[%d]: %d\n", i, lencount[i]);
	}
#endif 
}