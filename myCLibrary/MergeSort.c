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
* 2022.10.9 Sun
* 2023.1.30 Mon : Improved read
* 2024.1.20 Sat : Improved readability
*/