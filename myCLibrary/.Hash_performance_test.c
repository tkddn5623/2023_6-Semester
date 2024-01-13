#include <stdio.h>
#include <string.h>
#define __USE_MISC
#include <stdlib.h>
#undef __USE_MISC

#define lengthof(arr) ((int)(sizeof(arr) / sizeof(arr[0])))

#define HASH_MSB_BITS (10)
#define HASH_BLOCK_SIZE (1 << HASH_MSB_BITS)


struct simple_list {
	int size;
	int items[HASH_BLOCK_SIZE];
};

int hash_wrapper(int k, int mode);
int tiny_hash_i32(unsigned int k);
int tiny_hash_i64(unsigned long long k);
void performance_chaining(int hash_table[], const struct simple_list* num_set, int hash_mode);
void performance_linear_probing(int hash_table[], const struct simple_list* num_set, int hash_mode);
void _MergeSort_impl(int* list, int* sorted, const int left, const int right);
int* MergeSort(int* list, int size);

int main() {
	static int hash_table[HASH_BLOCK_SIZE];
	static int num_buffer[HASH_BLOCK_SIZE];
	static struct simple_list num_set;

	// Parameter 1: Num buffer size
	int num_buffer_size = HASH_BLOCK_SIZE * 50 / 100;
#ifdef GLIBC
	srandom(1);
#endif

	for (int i = 0; i < num_buffer_size; i++) {
		int element = -1;

		element = (i);
		//element = (i - (num_buffer_size / 2));
		//element = i * i;

#ifdef __GLIBC__
		element = random();
		printf("SHIT! (%d)\n", element);
#endif

		//printf("E: %d\n", element);

		num_buffer[i] = element;
	}

	// Below is the part about deduplication.
	MergeSort(num_buffer, num_buffer_size);
	num_set.items[num_set.size++] = num_buffer[0];

	for (int prev = num_buffer[0], i = 1; i < num_buffer_size; i++) {
		int cur = num_buffer[i];
		if (prev == cur) continue;
		prev = cur;
		num_set.items[num_set.size++] = cur;
	}

	// Below is the output part
	printf("HASH BLOCK SIZE: %d\n", HASH_BLOCK_SIZE);
	printf("KEY CARDINALITY: %d (load factor: %.3f)\n\n", num_set.size, (double)num_set.size / HASH_BLOCK_SIZE);

	performance_chaining(hash_table, &num_set, 0);
	performance_linear_probing(hash_table, &num_set, 0);

	performance_chaining(hash_table, &num_set, 1);
	performance_linear_probing(hash_table, &num_set, 1);
}

// Parameter 2: Hash function
int hash_wrapper(int k, int mode) {
	switch (mode) {
	case 0: return tiny_hash_i32(k);
	case 1: return tiny_hash_i64(k);
	default: exit(1);
	}
}

int tiny_hash_i32(unsigned int k) {
	return (k * 2654435769u) >> (32 - HASH_MSB_BITS);
}

int tiny_hash_i64(unsigned long long k) {
	return (k * 11400714819323198485llu) >> (64 - HASH_MSB_BITS);
}

void performance_chaining(int hash_table[], const struct simple_list* num_set, int hash_mode) {
	static int count[1000];

	memset(hash_table, 0, sizeof(hash_table[0]) * HASH_BLOCK_SIZE);
	memset(count, 0, sizeof(count));

	for (int sz = num_set->size, i = 0; i < sz; i++) {
		int h = hash_wrapper(num_set->items[i], hash_mode);
		hash_table[h]++;
	}

	for (int i = 0; i < HASH_BLOCK_SIZE; i++) {
		int c = hash_table[i];
		if (c == 0) continue;
		if (c < lengthof(count)) count[c]++;
		else count[lengthof(count) - 1]++;
	}

	for (int i = 0; i < lengthof(count); i++) {
		if (count[i] == 0) continue;
		printf("Count(chaining) %2d%s: %d\n", i, i < lengthof(count) - 1 ? " " : "+", count[i]);
	}
	putchar('\n');

}

void performance_linear_probing(int hash_table[], const struct simple_list* num_set, int hash_mode) {
	static int count_move[1000];
	static int count_chunk[1000];

	memset(hash_table, 0, sizeof(hash_table[0]) * HASH_BLOCK_SIZE);
	memset(count_move, 0, sizeof(count_move));
	memset(count_chunk, 0, sizeof(count_chunk));

	for (int sz = num_set->size, i = 0; i < sz; i++) {
		int j, h = hash_wrapper(num_set->items[i], hash_mode);
		for (j = 0; j < HASH_BLOCK_SIZE; j++) {
			if (hash_table[(h + j) % HASH_BLOCK_SIZE] == 0) break;
		}
		if (j == HASH_BLOCK_SIZE) {
			printf("Open addressing failed: Blocks overflowd.\n");
			return;
		}
		count_move[j < lengthof(count_move) ? j : lengthof(count_move) - 1]++;
		hash_table[(h + j) % HASH_BLOCK_SIZE]++;
	}

	for (int i = 0; i < lengthof(count_move); i++) {
		if (count_move[i] == 0) continue;
		printf("Count(linear_probing_insert) %2d%s: %d\n", i, i < lengthof(count_move) - 1 ? " " : "+", count_move[i]);
	}
	putchar('\n');

	int start = -1;
	for (int i = 0; i < HASH_BLOCK_SIZE; i++) {
		if (hash_table[i] == 0 && hash_table[(i + 1) % HASH_BLOCK_SIZE] != 0) {
			start = (i + 1) % HASH_BLOCK_SIZE;
			break;
		}
	}

	if (start == -1) {
		printf("Open addressing failed: All blocks connected. (i.e. size is %d)\n", num_set->size);
		return;
	}

	for (int len = 0, i = 0; i < HASH_BLOCK_SIZE; i++) {
		if (hash_table[(start + i) % HASH_BLOCK_SIZE] == 0) {
			if (len > 0) {
				count_chunk[len < lengthof(count_chunk) ? len : lengthof(count_chunk) - 1]++;
			}
			//count_chunk[0]++;
			len = 0;
		}
		else {
			len++;
		}
	}

	for (int i = 0; i < lengthof(count_chunk); i++) {
		if (count_chunk[i] == 0) continue;
		printf("Count(linear_probing_search) %2d%s: %d\n", i, i < lengthof(count_chunk) - 1 ? " " : "+", count_chunk[i]);
	}
	putchar('\n');

}

void _MergeSort_impl(int* list, int* sorted, const int left, const int right) {
	if (left >= right) return;
	const int mid = left + (right - left) / 2;
	_MergeSort_impl(list, sorted, left, mid);
	_MergeSort_impl(list, sorted, mid + 1, right);
	int idx, first, second;
	idx = left, first = left, second = mid + 1;
	while (first <= mid && second <= right) {
		if (list[first] <= list[second]) sorted[idx++] = list[first++];
		else sorted[idx++] = list[second++];
	}
	while (first <= mid)    sorted[idx++] = list[first++];
	while (second <= right) sorted[idx++] = list[second++];
	for (int i = left; i <= right; i++) list[i] = sorted[i];
}

int* MergeSort(int* list, int size) {
	int* sorted = calloc(size, sizeof(int)); if (!sorted) exit(1);
	_MergeSort_impl(list, sorted, 0, size - 1);
	free(sorted);
	return list;
}

/*
2024-01-13

Hash performance simple tester

This program compares the performance of hash table
chaining and open addressing (linear probing among them).

For chaining, the sizes of each list are output.
For open addressing, the sizes of each cluster are output.
*/