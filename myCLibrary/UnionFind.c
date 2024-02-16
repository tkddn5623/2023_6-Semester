#include <stdlib.h>

int UF_find(int disjset[], int key) {
    if (disjset[key] < 0) return key;
    else return disjset[key] = UF_find(disjset, disjset[key]);
}
void UF_union(int disjset[], int A, int B) {
    A = UF_find(disjset, A);
    B = UF_find(disjset, B);
    if (A == B) return;
    //disjset[A] += disjset[B];
    disjset[B] = A;
}

/*
int* UF_init(int maxsize) {
    int* disjset;
    if ((disjset = calloc(maxsize, sizeof(int))) == NULL) exit(1);
    memset(disjset, -1, sizeof(int) * maxsize);
    return disjset;
}
*/


/*
* 2022.9.5 Mon
* 
* 2023.7.5 Wed 
* The root value is changed to have -1.
* disjset[A] becomes root and contains the size of sets
*
* 2024.2.13 Tue
* UF_init is deprecated.
*/