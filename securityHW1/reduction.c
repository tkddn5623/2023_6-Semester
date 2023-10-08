#include <string.h>
#include "reduction.h"
void reduction(uint8_t dest[], const uint8_t src[], int destlen, int srclen, int pwbits) {
	int quotient = pwbits / 8;
	int reminder = pwbits % 8;
	memset(dest, 0, sizeof(uint8_t) * destlen);
	memcpy(&dest[destlen - quotient], &src[srclen - quotient], sizeof(uint8_t) * quotient);
	if (reminder) {
		dest[destlen - quotient - 1] = src[srclen - quotient - 1] & 0xf;
	}
}