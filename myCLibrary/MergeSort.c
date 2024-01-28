#include <stdlib.h>

typedef int Element;

void _MergeSort_impl(Element* list, Element* sorted, const int left, const int right) {
    if (left >= right) return;
    const int mid = left + (right - left) / 2;
    _MergeSort_impl(list, sorted, left, mid);
    _MergeSort_impl(list, sorted, mid + 1, right);
    int idx = left, first = left, second = mid + 1;
    while (first <= mid && second <= right) {
        if (list[first] <= list[second]) sorted[idx++] = list[first++];
        else sorted[idx++] = list[second++];
    }
    while (first <= mid)    sorted[idx++] = list[first++];
    while (second <= right) sorted[idx++] = list[second++];
    for (int i = left; i <= right; i++) list[i] = sorted[i];
}
Element* MergeSort(Element* list, int size) {
    Element* sorted = calloc(size, sizeof(Element)); if (!sorted) exit(1);
    _MergeSort_impl(list, sorted, 0, size - 1);
    free(sorted);
    return list;
}

/*
Integer Sort (2023.7.21 Fri.)

void _MergeSort_impl(int* list, int* sorted, const int left, const int right) {
    if (left >= right) return;
    const int mid = left + (right - left) / 2;
    _MergeSort_impl(list, sorted, left, mid);
    _MergeSort_impl(list, sorted, mid + 1, right);
    int idx = left, first = left, second = mid + 1;
    while (first <= mid && second <= right) {
        if (list[first] <= list[second]) sorted[idx++] = list[first++];
        else sorted[idx++] = list[second++];
    }
    while (first <= mid)    sorted[idx++] = list[first++];
    while (second <= right) sorted[idx++] = list[second++];
    for (int i = left; i <= right; i++) list[i] = sorted[i];
}
int* MergeSort(int* list, int size) {
    static int sorted[10000];
    _MergeSort_impl(list, sorted, 0, size - 1);
    return list;
}
*/

/*
Non recursive Merge sort (2024.01.28 Sun.)

But unimproved performance, poor readability

int* MergeSort(int* list, const int size) {
	static struct _callstack {
		int left;
		int right;
		int visited;
	} callstack[64];

	int callstack_top;
	int* sorted;

	if (!(sorted = calloc(size, sizeof(int)))) exit(1);

	callstack[(callstack_top = 0)] = (struct _callstack){ 0, size - 1, 0 };

	while (callstack_top > -1) {
		const int left = callstack[callstack_top].left;
		const int right = callstack[callstack_top].right;
		const int mid = left + (right - left) / 2;

		// Divide 
		if (left >= right) {
			callstack_top--;
			continue;
		}
		if (!callstack[callstack_top].visited) {
			callstack[callstack_top].visited = 1;
			callstack[++callstack_top] = (struct _callstack){ mid + 1, right, 0 };
			callstack[++callstack_top] = (struct _callstack){ left, mid, 0 };
			continue;
		}
		callstack_top--;

		// Merge
		int idx = left, first = left, second = mid + 1;
		while (first <= mid && second <= right) {
			if (list[first] <= list[second]) sorted[idx++] = list[first++];
			else sorted[idx++] = list[second++];
		}
		while (first <= mid)    sorted[idx++] = list[first++];
		while (second <= right) sorted[idx++] = list[second++];
		for (int i = left; i <= right; i++) list[i] = sorted[i];
	}

	free(sorted);
	return list;
}

/*
* 2022.10.9 Sun
* 2023.1.30 Mon : Improved read
* 2024.1.20 Sat : Improved readability
* 2024.1.28 Sun : Non recursive example added
*/