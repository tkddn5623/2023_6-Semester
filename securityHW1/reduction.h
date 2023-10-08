#ifndef REDUCTION_H
#define REDUCTION_H

#include <stdint.h>
#define REDUCTCHAIN (500)
void reduction(uint8_t dest[], const uint8_t src[], int destlen, int srclen, int pwbits);

#endif