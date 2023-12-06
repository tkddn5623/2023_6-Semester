#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BANNER \
	"Welcome to Security final exam, good luck!"

int target;

void bounce(char *str) {
	printf(str);
}

int main(int argc, char **argv) {
	char buf[4096];
	printf("%s\n", BANNER);

	if (read(0, buf, sizeof(buf) - 1) <= 0) {
		exit(EXIT_FAILURE);
	}
	bounce(buf);

	if (target == 0x64457875) {
		puts("Well done, the 'target' variable has been changed correctly! You've finished second problem!");
	} else {
		printf("Better luck next time - got 0x%08x, wanted 0x64457875!\n", target);
	}
	exit(0);
}
