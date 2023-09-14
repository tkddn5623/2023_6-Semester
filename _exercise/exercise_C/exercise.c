/*
* Simple pdf splicer
* 2023. 7. 21. Fri.
* 2023. 9. 14. Thu.
*/
#include <stdio.h>
#include <string.h>
#define ODD(i)  ((i) * 2 - 1)
#define EVEN(i) ((i) * 2)

//  Change Below  /////////////////////////////////////////////////
#define MAXBUFSIZE  (5 * (1 << 20))  // Each page less than 5MB
#define MAXPAGE     ((int)1e4)       // Must be 10, 100, 1000 ...
#define MAXFILENAME (200)
#define OUTINDEX(i) (ODD(i))
const char* dirpath = "C:/Users/tkddn/Desktop/pdfwork/merge/";
const char* prefix =  "Computer Networking - A Top Down Approach (2020)_ºÎºÐ";
const char* suffix =  ".pdf";
const char* outname = "Computer Networking(2020) - ";
//  Don't Change Below  ///////////////////////////////////////////


static char buffer_text[MAXBUFSIZE];
static char filename1[MAXFILENAME];
static char filename2[MAXFILENAME];
char*
writeint(char* str, int n) {
	int i = 0, j = MAXPAGE;
	while (j > 1 && !(n / j)) { j /= 10; }
	do {
		str[i++] = '0' | n / j;
		n %= j;
		j /= 10;
	} while (j);
	str[i++] = '\0';
	return str;
}
int
main() {
	char numstr[10];
	int i;
	FILE* fin, * fout;
	for (i = 1;i <= MAXPAGE; i++) {
		int input_sz;
		memset(buffer_text, 0, sizeof(buffer_text));

		memset(filename1, 0, sizeof(filename1));
		memset(filename2, 0, sizeof(filename2));

		strcat(filename1, dirpath);
		strcat(filename1, prefix);
		strcat(filename1, writeint(numstr, i));
		strcat(filename1, suffix);

		strcat(filename2, dirpath);
		strcat(filename2, outname);
		strcat(filename2, writeint(numstr, OUTINDEX(i)));
		strcat(filename2, suffix);

		if (!(fin = fopen(filename1, "rb"))) {
			printf("File(in) open error\n");
			break;
		}
		if (!(fout = fopen(filename2, "wb"))) {
			printf("File(out) open error\n");
			break;
		}
		fseek(fin, 0, 2);
		input_sz = ftell(fin);
		fseek(fin, 0, 0);

		fread(buffer_text, 1, input_sz, fin);
		fwrite(buffer_text, 1, input_sz, fout);

		fclose(fin);
		fclose(fout);
	}
}