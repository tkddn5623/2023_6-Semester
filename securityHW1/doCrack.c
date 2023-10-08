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
static void str_to_uint8v(const char* s) {

}
static int _tableMergeSort_impl() {

}
int tableMergeSort() {

}
void readRainbowTable(int pwbits, const char* rainbowPath) {
	const int SPACEBOUND = 1 << (pwbits / 2);
	struct rainbowEntry* rainbowEntries;
	FILE* fi;
	if (!(fi = fopen(rainbowPath, "rb"))) {
		printf("Error: Rainbow file open error\n");
		exit(1);
	}
	if (!(rainbowEntries = calloc(SPACEBOUND, sizeof(struct rainbowEntry)))) exit(1);
	fread(rainbowEntries, 1, sizeof(struct rainbowEntry) * SPACEBOUND, fi);
	for (int i = 0; i < SPACEBOUND; i++) {
		printf("KeyX --> ");
		for (int j = 0; j < 16; j++) {
			printf("%02x", rainbowEntries[i].x[j]);
		}
		putchar('\n');
		printf("KeyY --> ");
		for (int j = 0; j < 16; j++) {
			printf("%02x", rainbowEntries[i].y[j]);
		}
		putchar('\n');
		putchar('\n');
	}



	free(rainbowEntries);
}
int findRainbowTable(int pwbits) {

}
int main(int argc, char* argv[]) {
	uint8_t cypher[16];
	int pwbits;
	printf("!");
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
	printf("Argv2:[%s]\n", argv[2]);
	readRainbowTable(pwbits, "rainbow");
	//findRainbowTable(pwbits, "rainbow");
}