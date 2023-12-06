#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BANNER \
	"Welcome to Security final exam, good luck!"

char *gets(char *);

void complete_level() {
	printf("Congratulations, you've finished first problem. Well done!\n");
	exit(0);
}

int main(int argc, char **argv) {
	struct {
		char buffer[64];
		volatile int (*fp)();
	} locals;

	printf("%s\n", BANNER);

	locals.fp = NULL;
	gets(locals.buffer);

	if (locals.fp) {
		printf("calling function pointer @ %p\n", locals.fp);
		fflush(stdout);
		locals.fp();
	}
	else {
		printf("function pointer remains unmodified :( better luck next time!\n");
	}
	exit(0);
}
