#include <stdlib.h>
#include <string.h>
#include "LinearSieve.h"

int* getPrimeList(const int maxprime, int* psize) {
	int length = 0;
	int* factorList = calloc(maxprime + 2, sizeof(int)); if (!factorList) exit(1);
	int* primeList = calloc(maxprime, sizeof(int)); if(!primeList) exit(1);
	int* shrunkList;

	factorList[0] = 0; factorList[1] = 0;
	for (int i = 2; i <= maxprime; i++) {
		if (!factorList[i]) primeList[length++] = i;
		for (int j = 0; j < length; j++) {
			if (i * primeList[j] > maxprime) break;
			factorList[i * primeList[j]] = 1;
			if (i % primeList[j] == 0) break;
		}
	}
	free(factorList);

	shrunkList = calloc(length, sizeof(int)); if(!shrunkList) exit(1);
	memcpy(shrunkList, primeList, length * sizeof(int));
	free(primeList);

	if (psize != NULL) *psize = length;
	return shrunkList;
}

int* getFactorList(const int maxprime) {
	int length = 0;
	int* factorList = calloc(maxprime + 2, sizeof(int)); if (!factorList) exit(1);
	int* primeList = calloc(maxprime, sizeof(int)); if (!primeList) exit(1);
	
	factorList[0] = 0; factorList[1] = 0;
	for (int i = 2; i <= maxprime; i++) {
		if (!factorList[i]) primeList[length++] = i;
		for (int j = 0; j < length; j++) {
			if (i * primeList[j] > maxprime) break;
			factorList[i * primeList[j]] = primeList[j];
			if (i % primeList[j] == 0) break;
		}
	}
	free(primeList);
	return factorList;
}