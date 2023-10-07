#include <stdio.h>  ////////////////////////////////////////////
#include <stdlib.h> /// Date:   2023-10-17                   ///
#include <string.h> /// Author: jung sang woo                ///
#include <stdint.h> ///                                      ///
#include "aes.h"    /// This is third party AES header       ///
////////////////////////////////////////////
#define REDUCTCHAIN (3)
#define BUFSIZE     (10000)

static char buffer[BUFSIZE];
static int PWBITS;

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
uint8_t* uint8v_add1(uint8_t u8vec[], int length) {
	while (length-- > 0) {
		if ((u8vec[length] += 1) == 0) break;
	}
	return u8vec;
}
void reduction(uint8_t dest[], const uint8_t src[], int destlen, int srclen) {
	int quotient = PWBITS / 8;
	int reminder = PWBITS % 8;
	memset(dest, 0, sizeof(uint8_t) * destlen);
	if (reminder) {
		dest[destlen - quotient - 1] = (src[0] >> 4);
		for (int i = 0; i < quotient; i++) {
			dest[destlen - quotient + i] = (src[i] << 4) | (src[i + 1] >> 4);
		}
	}
	else {
		memcpy(&dest[destlen - quotient], &src[0], sizeof(uint8_t) * quotient);
	}


}
int makeRainbowTable(const char* outputPath) {
	FILE* fo;
	if (!(fo = fopen(outputPath, "wb"))) {
		printf("Error: Output file open error\n");
		exit(1);
	}
	const int SPACEBOUND = integerSqrt(1 << PWBITS);
	struct AES_ctx ctx;
	uint8_t plain[16];         //128 bit
	uint8_t key1[16];          //128 bit
	uint8_t key2[16];          //128 bit

	memset(plain, 0, sizeof(plain));
	memset(key1, 0, sizeof(key1));


	/*for (int i = 0; i < 16; i++) {
		printf("%02x", plain[i]);
	}
	putchar('\n');*/

	// for (int i = 0; i < SPACEBOUND; i++) {
	for (int i = 0; i < 2; i++) {
		fwrite(key1, 1, sizeof(key1), fo);
		memcpy(key2, key1, sizeof(key2));
		for (int j = 0; j < REDUCTCHAIN; j++) {
			AES_init_ctx(&ctx, key2);
			AES_ECB_encrypt(&ctx, plain);
			// In this time plain is the Hash result.
			printf("In this time, plain:\n");
			for (int i = 0; i < 16; i++) {
				printf("%02x", plain[i]);
			}
			putchar('\n');

			reduction(key2, plain, 16, 16);
			memset(plain, 0, sizeof(plain));

			printf("Yes, now my key:\n");
			for (int i = 0; i < 16; i++) {
				printf("%02x", key2[i]);
			}
			putchar('\n');
		}
	}






	fclose(fo);
}
int main(int argc, char* argv[]) {
	/*if (argc != 2) {
		printf("Usage: Enter one command line argument. (non-negative integer)\n");
		exit(1);
	}
	if (argv_valid_check(argv[1]) || (PWBITS = str_to_int(argv[1])) <= 0) {
		printf("Usage: Please enter a non-negative integer as argument\n");
		exit(1);
	}
	if (PWBITS > 32 || PWBITS % 4) {
		printf("Usage: the argument is wrong ( <= 32 %% multiple of 4) \n");
		exit(1);
	}*/
	PWBITS = 20;
	makeRainbowTable("rainbow");

}