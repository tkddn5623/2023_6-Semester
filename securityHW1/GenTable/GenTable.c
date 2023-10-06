#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "../aes/aes.h"
#define PLAINTEXT (0x00000000000000000000000000000000)
#define BUFSIZE (10000)

static char buffer[BUFSIZE];

int argv_valid_check(const char* s) {
	int a;
	while ((a = *s++)) {
		if (a != '-' && a < '0' && a > '9') return 1;
	}
	return 0;
}
int str_to_int(const char* s) {
	int a, b, c;
	while ((c = *s++) && c < '-');
	for (b = c < '0' ? 0 : c & 0xf; (a = *s++) >= '0'; b = b * 10 + (a & 0xf));
	return c == '-' ? -b : b;
}
int makeRainbowTable(int N, const char* outputPath) {
	FILE* fo;
	if (!(fo = fopen(outputPath, "w"))) {
		printf("Error: Output file open error\n");
		exit(1);
	}
	struct AES_ctx ctx;
	uint8_t key[16] = { 0 };
	uint8_t plain[16] = { 0 };
	AES_init_ctx(&ctx, key);
	AES_ECB_encrypt(&ctx, plain);
	
	





	fclose(fo);
}
int main(int argc, char* argv[]) {
	int N;
	if (argc != 2) {
		printf("Usage: Enter one command line argument. (non-negative integer)\n");
		exit(1);
	}
	if (argv_valid_check(argv[1]) || (N = str_to_int(argv[1])) <= 0) {
		printf("Usage: Please enter a non-negative integer as argument\n");
		exit(1);
	}
	if (N > 32 || N % 4) {
		printf("Usage: the argument is wrong ( <= 32 %% multiple of 4) \n");
		exit(1);
	}
	N = 20;
	makeRainbowTable(N, "rainbow");
}