#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "aes.h"
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
char* aes_to_str(char buffer[], uint8_t key[], int length) {
	uint8_t k;
	for (int i = 0; i < length; i++) {
		
	}
	return NULL;
}
int integerSqrt(int N) {
	int root, l = 0, r = ~(1 << 31);
	while (l <= r) {
		int mid = l + (r - l) / 2;
		if ((long long)mid * mid <= N) {
			l = mid + 1;
			root = mid;
		}
		else {
			r = mid - 1;
		}
	}
	return root;
}
void reduction() {

}
int makeRainbowTable(int N, const char* outputPath) {
	FILE* fo;
	if (!(fo = fopen(outputPath, "wb"))) {
		printf("Error: Output file open error\n");
		exit(1);
	}
	const int SPACEBOUND = integerSqrt(1 << N);
	struct AES_ctx ctx;
	uint8_t plain[16];         //128 bit
	uint8_t key[16];           //128 bit

	memset(plain, 0, sizeof(plain));
	memset(key, 0, sizeof(key));

	AES_init_ctx(&ctx, key);
	AES_ECB_encrypt(&ctx, plain);
	for (int i = 0; i < 16; i++) {
		printf("[%2x] ", plain[i]);
	}
	putchar('\n');

	for (int i = 0; i < SPACEBOUND; i++) {

	}






	fclose(fo);
}
int main(int argc, char* argv[]) {
	int N;
	for (int i = 0; i <= 128; i++) {
		printf("%d: %d\n", i, integerSqrt(i));
	}
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