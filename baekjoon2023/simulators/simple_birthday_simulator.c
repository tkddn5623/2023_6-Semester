/*
* 2024-01-14 Sun
* 
* Simple hash collision expected value calculator
* Super simple implementation with DFS
* 
* Example: 
* (64, 32) => (38.6, 25.3, 6.6)
*
*/

#include <stdio.h>

double expect = 0.0;

void solve1536(const int block_size, const int element_size, int depth, int occupied, double probability) {
	if (depth >= element_size) {
		expect += probability * (block_size - occupied);
		return;
	}
	solve1536(block_size, element_size, depth + 1, occupied + 1, probability * (block_size - occupied) / block_size);
	solve1536(block_size, element_size, depth + 1, occupied, probability * occupied / block_size);
}
int main() {
	int block_size, element_size;

	block_size = 64;
	element_size = 32;

	solve1536(block_size, element_size, 1, 1, 1.0);

	printf("Expected value of an empty block:\n= %.2f\n", expect);
	printf("Expected value of at least one filled block:\n= %.2f\n", block_size - expect);
	printf("Difference between the number of elements and the expected value of filled blocks:\n= %.2f\n", element_size - (block_size - expect));
}

