#include <stdlib.h>

int UF_find(int* roots, int key) {
    if (roots[key] < 0) return key;
    else return roots[key] = UF_find(roots, roots[key]);
}
void UF_union(int* roots, int A, int B) {
    A = UF_find(roots, A);
    B = UF_find(roots, B);
    if (A == B) return;
    //roots[A] += roots[B];
    roots[B] = A;
}

/*
int* UF_init(int maxsize) {
    int* roots;
    if ((roots = calloc(maxsize, sizeof(int))) == NULL) exit(1);
    memset(roots, -1, sizeof(int) * maxsize);
    return roots;
}
*/


/*
* 2022.9.5 Mon
* 
* 2023.7.5 Wed 
* The root value is changed to have -1.
* roots[A] becomes root and contains the size of sets
*
* 2024.2.13 Tue
* UF_init is deprecated.
*/