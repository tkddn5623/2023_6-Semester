#include <stdio.h>     /////////////////////////////////////////////////
#include <stdlib.h>    /// Date:   2023-10-08
#include <string.h>    /// Author: jung sang woo
#include <stdint.h>    ///
#include "aes.h"       /// This is third party AES header from github
#include "reduction.h" /// This is my reduction header
////////////////////////////////////////////////////////////////////////

struct rainbowEntry {
	uint8_t x[16];
	uint8_t y[16];
};

static int argv_valid_check(const char* s) {
	int a;
	while ((a = *s++)) {
		if (a != '-' && a < '0' && a > '9') return 1;
	}
	return 0;
}
static int str_to_int(const char* s) {
	int a, b, c;
	while ((c = *s++) && c < '-');
	for (b = c < '0' ? 0 : c & 0xf; (a = *s++) >= '0'; b = b * 10 + (a & 0xf));
	return c == '-' ? -b : b;
}
static uint8_t char_to_4bit(char ch) {
	if (ch >= '0' && ch <= '9') {
		return ch - '0';
	}
	else if (ch >= 'a' && ch <= 'f') {
		return ch - 'a' + 10;
	}
	else {
		printf("Usage: the argument is wrong ( 0-9, a-f is allowed ) \n");
		exit(1);
	}
}
static void str_to_uint8v(uint8_t buf[], const char* s, int buflen) {
	for (int i = 0; i < buflen; i++) {
		buf[i] = char_to_4bit(*s++) << 4;
		buf[i] |= char_to_4bit(*s++);
	}
}
static int uint8v_cmp(const uint8_t u8vec1[], const uint8_t u8vec2[], int length) {
	for (int i = 0; i < length; i++) {
		if (u8vec1[i] > u8vec2[i]) return 1;
		else if (u8vec1[i] < u8vec2[i]) return -1;
	}
	return 0;
}
static void _tableMergeSort_impl(struct rainbowEntry* list, struct rainbowEntry* sorted, const int left, const int right) {
	if (left >= right) return;
	const int mid = left + (right - left) / 2;
	_tableMergeSort_impl(list, sorted, left, mid);
	_tableMergeSort_impl(list, sorted, mid + 1, right);
	int idx, first, second;
	idx = left, first = left, second = mid + 1;
	while (first <= mid && second <= right) {
		if (uint8v_cmp(list[first].y, list[second].y, 16) < 1) sorted[idx++] = list[first++];
		else sorted[idx++] = list[second++];
	}
	while (first <= mid)    sorted[idx++] = list[first++];
	while (second <= right) sorted[idx++] = list[second++];
	for (int i = left; i <= right; i++) list[i] = sorted[i];
}
void tableSort(struct rainbowEntry list[], int size) {
	struct rainbowEntry* sorted;
	if (!(sorted = calloc(size, sizeof(struct rainbowEntry)))) exit(1);
	_tableMergeSort_impl(list, sorted, 0, size - 1);
	free(sorted);
}
int tableSearch(struct rainbowEntry list[], uint8_t key[], int listsize) {
	int left = 0, mid, cmp;
	listsize = listsize - 1;
	while (left <= listsize) {
		mid = left + (listsize - left) / 2;
		switch (cmp = uint8v_cmp(list[mid].y, key, 16)) {
		case -1: left = mid + 1; break;
		case 0: return mid;
		case 1: listsize = mid - 1; break;
		}
	}
	return -1;
}
void readRainbowTable(int pwbits, const uint8_t cipher[], const char* rainbowPath) {
	FILE* fi;
	if (!(fi = fopen(rainbowPath, "rb"))) {
		printf("Error: Rainbow file open error\n");
		exit(1);
	}
	const int SPACEBOUND = 1 << (pwbits / 2);
	struct AES_ctx ctx;
	uint8_t plain[16];  //128 bit
	uint8_t key[16];    //128 bit
	struct rainbowEntry* rainbowEntries;
	int rainbowEntryIndex, totalAES = 0;
	if (!(rainbowEntries = calloc(SPACEBOUND, sizeof(struct rainbowEntry)))) exit(1);
	fread(rainbowEntries, 1, sizeof(struct rainbowEntry) * SPACEBOUND, fi);
	tableSort(rainbowEntries, SPACEBOUND);
	
	reduction(key, cipher, 16, 16, pwbits); // Reduction function
	for (int i = 0; i < REDUCTCHAIN; i++) {
		if ((rainbowEntryIndex = tableSearch(rainbowEntries, key, SPACEBOUND)) > -1) {
			break;
		}
		memset(plain, 0, sizeof(plain));
		totalAES++;
		AES_init_ctx(&ctx, key);
		AES_ECB_encrypt(&ctx, plain);   // Third-party Hash function
		reduction(key, plain, 16, 16, pwbits); // Reduction function
	}
	printf("Idx was %d\n", rainbowEntryIndex);
	for (int i = 0; i < 16; i++) {
		printf("%02x", rainbowEntries[rainbowEntryIndex].x[i]);
	}
	putchar('\n');
	for (int i = 0; i < 16; i++) {
		printf("%02x", rainbowEntries[rainbowEntryIndex].y[i]);
	}
	putchar('\n');

	
	if (rainbowEntryIndex == -1) {
		printf("failure\n");
	}
	else {
		memcpy(key, rainbowEntries[rainbowEntryIndex].x, sizeof(key));
		for (int i = 0; i < REDUCTCHAIN; i++) {
			memset(plain, 0, sizeof(plain));
			totalAES++;
			AES_init_ctx(&ctx, key);
			AES_ECB_encrypt(&ctx, plain);    // Third-party Hash function
			if (!uint8v_cmp(cipher, plain, 16)) {
				for (int j = 0; j < 16; j++) { printf("%02x", key[j]); }
				putchar('\n');
				break;
			}
			reduction(key, plain, 16, 16, pwbits); // Reduction function
		}
	}
	printf("the number of times AES: %d\n", totalAES);
	free(rainbowEntries);
}
int findRainbowTable(int pwbits) {

}
int main(int argc, char* argv[]) {
	uint8_t cipher[16];
	int pwbits;
	if (argc != 3) {
		printf("Usage: Enter two command line argument. (non-negative integer, 128bit hex number)\n");
		exit(1);
	}
	if (argv_valid_check(argv[1]) || (pwbits = str_to_int(argv[1])) <= 0) {
		printf("Usage: Please enter a non-negative integer as argument\n");
		exit(1);
	}
	if (pwbits > 32 || pwbits % 4) {
		printf("Usage: the argument is wrong ( <= 32 %% multiple of 4) \n");
		exit(1);
	}
	if (strlen(argv[2]) != 32) {
		printf("Usage: the argument is wrong ( must be 128bit (i.e. 32 char)) \n");
		exit(1);
	}
	str_to_uint8v(cipher, argv[2], 16);
	readRainbowTable(pwbits, cipher, "rainbow");
	//findRainbowTable(pwbits, "rainbow");
}