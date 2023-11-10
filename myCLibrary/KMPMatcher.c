#include <stdlib.h>
#include <string.h>
#define MAXLEN (1000000)
int* KMP_Matcher(const char text[], const char pattern[]) {
	static int prefix[MAXLEN];
	const int len_text = strlen(text);
	const int len_ptrn = strlen(pattern);
	int* answerlist;
	int answersize = 0;
	if (!(answerlist = calloc(len_text - len_ptrn + 2, sizeof(int)))) exit(1);
	if (len_text < len_ptrn) return answerlist;

	// Compute-Prefix-Function
	prefix[1] = 0;
	for (int k = 0, i = 1; i < len_ptrn; i++) {
		while (k > 0 && pattern[i] != pattern[k])
			k = prefix[k];
		if (pattern[i] == pattern[k])
			k = k + 1;
		prefix[i + 1] = k;
	}

	// KMP-Matcher
	for (int q = 0, i = 0; i < len_text; i++) {
		while (q > 0 && text[i] != pattern[q])
			q = prefix[q];
		if (text[i] == pattern[q])
			q = q + 1;
		if (q == len_ptrn) {
			q = prefix[q];
			answerlist[++answersize] = i - len_ptrn + 2;
			//answerlist[++answersize] = i - len_ptrn + 1;
		}
	}
	answerlist[0] = answersize;
	return answerlist;
}