#include <stdio.h>     ////////////////////////////////////////////
#include <stdlib.h>    /// Date:   2023-10-08                   ///
#include <string.h>    /// Author: jung sang woo                ///
#include <stdint.h>    ///                                      ///
#include "aes.h"       /// This is third party AES header       ///
#include "reduction.h" /// This is my reduction header          ///
///////////////////////////////////////////////////////////////////
uint8_t _answer20_1[16] = {
	0x8d,0xe0,0xbc,0xff,0xe5,0x87,0xf6,0x3e,0xd5,0xc8,0x23,0xdc,0xf9,0xbf,0x51,0x31
};
uint8_t _answer20_2[16] = {
	0xf7,0xef,0x41,0x3c,0xc5,0x1d,0xf0,0x4a,0xbf,0x68,0x72,0xdb,0x31,0x5e,0x69,0x4b
};
uint8_t _answer24_1[16] = {
	0xed,0x07,0x8d,0x9b,0x52,0x7a,0x81,0xfe,0x47,0x25,0x22,0x8d,0x88,0xb6,0x64,0xae
};
uint8_t _answer24_2[16] = {
	0xae,0x95,0x5b,0x02,0x7a,0x3d,0x0c,0xb5,0x40,0x1b,0x63,0xb4,0xd2,0x6a,0x10,0xba
};
uint8_t _answer28_1[16] = {
	0x86,0x52,0x70,0x77,0xe1,0xcb,0x39,0xb6,0xb2,0xe6,0xf4,0x14,0xb1,0xa7,0x58,0xf6
};
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
int integerSqrt(int N) {
	int root = 0, l = 0, r = ~(1 << 31);
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
		if ((u8vec[length] += 1)) break;
	}
	return u8vec;
}
int uint8v_cmp(const uint8_t u8vec1[], const uint8_t u8vec2[], int length) {
	for (int i = 0; i < length; i++) {
		if (u8vec1[i] != u8vec2[i]) return 1;
	}
	return 0;
}
void makeRainbowTable(int pwbits, const char* outputPath) {
	/*FILE* fo;
	if (!(fo = fopen(outputPath, "wb"))) {
		printf("Error: Output file open error\n");
		exit(1);
	}*/
	const int SPACEBOUND = integerSqrt(1 << pwbits);
	struct AES_ctx ctx;
	uint8_t plain[16];         //128 bit
	uint8_t key1[16];          //128 bit
	uint8_t key2[16];          //128 bit

	memset(key1, 0, sizeof(key1));
	for (int i = 0; i < SPACEBOUND; i++) {
		/*printf("Key1 -->\n");
		for (int j = 0; j < 16; j++) {
			printf("%02x", key1[j]);
		}
		putchar('\n');*/
		//fwrite(key1, 1, sizeof(key1), fo);
		memcpy(key2, key1, sizeof(key2));
		for (int j = 0; j < REDUCTCHAIN; j++) {
			memset(plain, 0, sizeof(plain));
			AES_init_ctx(&ctx, key2);
			AES_ECB_encrypt(&ctx, plain);   // Hash function
			// In this time plain is the Hash result.
			/*for (int k = 0; k < 16; k++) {
				printf("%02x", key2[k]);
			}
			printf(" -> ");
			for (int k = 0; k < 16; k++) {
				printf("%02x", plain[k]);
			}
			putchar('\n');*/
			if (!uint8v_cmp(plain, _answer20_2, 16)) {
				printf("The (%d : %d)th try. (Bound: %d)\n", i, j, SPACEBOUND);
				for (int k = 0; k < 16; k++) {
					printf("%02x", key2[k]);
				}
				printf(" -> ");
				for (int k = 0; k < 16; k++) {
					printf("%02x", plain[k]);
				}
				putchar('\n');
			}
			reduction(key2, plain, 16, 16, pwbits); // Reduction function
		}
		//fwrite(key2, 1, sizeof(key2), fo);
		uint8v_add1(key1, 16);
	}
	//fclose(fo);
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