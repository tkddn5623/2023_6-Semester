void string_getline(char* dest) {
	for (*dest = 0, fgets(dest, BUFMAX, stdin); *dest >= ' '; dest++);; *dest = 0;
}
int string_tokenizer(char* tokens[], char* str) {
	int ch, i = 0;
	do {
		while ((ch = *str) == ' ') *str++ = '\0';
		if (ch) tokens[i++] = str++;
		while ((ch = *str) != ' ' && ch) str++;
	} while (ch);
	return i;
}
int string_compare(const char* a, const char* b) {
	while (*a++ && *a == *b) a++, b++;
	return *a - *b;
}
void string_copy(char* a, const char* b) {
	while (*a = *b++);
}
int string_length(const char* a) {
	const char* b = a;
	while (*b) b++;
	return b - a;
}

/*
// Tokenizer <string.h> version

#define MAXTOK (999)
	char* tokens[MAXTOK];
	int tokens_size;
	tokens[(tokens_size = 0)] = strtok(buf, " ");
	while (++tokens_size < MAXTOK && (tokens[tokens_size] = strtok(NULL, " ")));

*/

/*
* 2024.2.5 Mon
* <string.h> imitation
* Reference of {compare, copy}: bloodstrawberry.tistory.com
*/