#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>

static char* in;
static struct {
	char buf[5000001];
	int idx;
} out;
void writeint(int n) {
	int j = 1000;
	while (j > 1 && !(n / j)) { j /= 10; }
	do { out.buf[out.idx++] = '0' | n / j; n %= j; } while (j /= 10);
	out.buf[out.idx++] = '\n';
}
int readint() {
	int a, b;
	while ((a = *in++) && a < '0');
	for (b = a & 0xf; (a = *in++) >= '0'; b = b * 10 + (a & 0xf));
	return b;
}
void IOinit() {
	struct stat st;
	fstat(0, &st);
	if ((in = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, 0, 0)) == MAP_FAILED)
		_exit(1);
}
/*
static char* in;
static struct {
	char buf[5000001];
	int idx;
} out;
void writeint(int n) {
	int j = 1000;
	if (n < 0) { out.buf[out.idx++] = '-'; n = -n; }
	while (j > 1 && !(n / j)) { j /= 10; }
	do { out.buf[out.idx++] = '0' | n / j; n %= j; } while (j /= 10);
	out.buf[out.idx++] = '\n';
}
int readint() {
	int a, b, c;
	while ((c = *in++) && c < '-');
	for (b = c < '0' ? 0 : c & 0xf; (a = *in++) >= '0'; b = b * 10 + (a & 0xf));
	return c == '-' ? -b : b;
}
*/
void solve15552() {
	int T = readint();
	int a, b;
	while (T--) {
		a = readint();
		b = readint();
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