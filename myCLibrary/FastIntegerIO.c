#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>

static char* in;
static struct {
	char buf[5000001];
	int idx;
} out;
void write_int(int n) {
	int j = 1000;
	while (j > 1 && !(n / j)) { j /= 10; }
	do { out.buf[out.idx++] = '0' | n / j; n %= j; } while (j /= 10);
	out.buf[out.idx++] = '\n';
}
int read_int() {
	int a, b;
	while ((a = *in++) && a < '0');
	for (b = a & 0xf; (a = *in++) >= '0'; b = b * 10 + (a & 0xf));
	return b;
}
void read_map() {
	struct stat st;
	fstat(0, &st);
	if ((in = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, 0, 0)) == MAP_FAILED)
		_exit(1);
}
/*
void read_whole() {
	fseek(stdin, 0, 2);
	int input_sz = ftell(stdin);
	if (!(in = calloc(input_sz, sizeof(char)))) exit(1);
	fseek(stdin, 0, 0);
	fread(in, 1, input_sz, stdin);
}
*/

/*
static char* in;
static struct {
	char buf[5000001];
	int idx;
} out;
void write_int(int n) {
	int j = 1000;
	if (n < 0) { out.buf[out.idx++] = '-'; n = -n; }
	while (j > 1 && !(n / j)) { j /= 10; }
	do { out.buf[out.idx++] = '0' | n / j; n %= j; } while (j /= 10);
	out.buf[out.idx++] = '\n';
}
int read_int() {
	int a, b, c;
	while ((c = *in++) && c < '-');
	for (b = c < '0' ? 0 : c & 0xf; (a = *in++) >= '0'; b = b * 10 + (a & 0xf));
	return c == '-' ? -b : b;
}
*/
void solve15552() {
	int T = read_int();
	int a, b;
	while (T--) {
		a = read_int();
		b = read_int();
		writeint(a + b);
	}
	write(1, out.buf, out.idx);
}
int main() {
	struct stat st;
	fstat(0, &st);
	if ((in = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, 0, 0)) == MAP_FAILED)
		return 1;
	solve15552();
	munmap(in, st.st_size);
}

/*
#include <sys/stat.h>
#include <sys/mman.h>

static char* map;

void _map() {
	struct stat st;
	fstat(0, &st);
	if ((map = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, 0, 0)) == MAP_FAILED) return;
}

// Use _exit or exit
*/
