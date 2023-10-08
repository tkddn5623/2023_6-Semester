#include <stdio.h>     /////////////////////////////////////////////////
#include <stdlib.h>    /// Date:   2023-10-08
#include <string.h>    /// Author: jung sang woo
#include <stdint.h>    ///
#include "aes.h"       /// This is third party AES header from github
#include "reduction.h" /// This is my reduction header
////////////////////////////////////////////////////////////////////////
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
static uint8_t* uint8v_add1(uint8_t u8vec[], int length) {
	while (length-- > 0) {
		if ((u8vec[length] += 1)) break;
	}
	return u8vec;
}
static int uint8v_cmp(const uint8_t u8vec1[], const uint8_t u8vec2[], int length) {
	for (int i = 0; i < length; i++) {
		if (u8vec1[i] != u8vec2[i]) return 1;
	}
	return 0;
}
void makeRainbowTable(int pwbits, const char* outputPath) {
	FILE* fo;
	if (!(fo = fopen(outputPath, "wb"))) {
		printf("Error: Output file open error\n");
		exit(1);
	}
	const int SPACEBOUND = 1 << (pwbits / 2);
	struct AES_ctx ctx;
	uint8_t plain[16];  //128 bit
	uint8_t key1[16];   //128 bit
	uint8_t key2[16];   //128 bit
	memset(key1, 0, sizeof(key1));
	for (int i = 0; i < SPACEBOUND; i++) {
		fwrite(key1, 1, sizeof(key1), fo);
		memcpy(key2, key1, sizeof(key2));
		for (int j = 0; j < REDUCTCHAIN; j++) {
			memset(plain, 0, sizeof(plain));
			AES_init_ctx(&ctx, key2);
			AES_ECB_encrypt(&ctx, plain);    // Third-party Hash function
			reduction(key2, plain, 16, 16, pwbits); // Reduction function
		}
		fwrite(key2, 1, sizeof(key2), fo);
		uint8v_add1(key1, 16);
	}
	fclose(fo);
}
int main(int argc, char* argv[]) {
	int pwbits;
	if (argc != 2) {
		printf("Usage: Enter one command line argument. (non-negative integer)\n");
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
	makeRainbowTable(pwbits, "rainbow");
}