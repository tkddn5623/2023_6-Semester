#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>

static struct IOBuffer {
    int rbi;
    int wbi;
    char* rb;
    char* wb;
} _buf;

void write_int(int n) {
	int m = 1000;
	while (m > 1 && !(n / m)) { m /= 10; }
	do { _buf.wb[_buf.wbi++] = '0' | n / m; n %= m; } while (m /= 10);
	_buf.wb[_buf.wbi++] = '\n';
}
int read_int() {
	int a, b;
	while ((a = _buf.rb[_buf.rbi++]) && a < '0');
	for (b = a & 0xf; (a = _buf.rb[_buf.rbi++]) >= '0'; b = b * 10 + (a & 0xf));
	return b;
}
void read_map() {
	struct stat st;
	fstat(0, &st);
	if ((_buf.rb = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, 0, 0)) == MAP_FAILED)
		_exit(1);
}

/* Minus integer version

static struct IOBuffer {
    int rbi;
    int wbi;
    char* rb;
    char* wb;
} _buf;

void write_int(int n) {
    int j = 1000;
    if (n < 0) { _buf.wb[_buf.wbi++] = '-'; n = -n; }
    while (j > 1 && !(n / j)) { j /= 10; }
    do { _buf.wb[_buf.wbi++] = '0' | n / j; n %= j; } while (j /= 10);
    _buf.wb[_buf.wbi++] = '\n';
}
int read_int() {
    int a, b, c;
    while ((c = _buf.rb[_buf.rbi++]) && c < '-');
    for (b = c < '0' ? 0 : c & 0xf; (a = _buf.rb[_buf.rbi++]) >= '0'; b = b * 10 + (a & 0xf));
    return c == '-' ? -b : b;
}

*/

/* Fread version

void read_whole() {
	fseek(stdin, 0, 2);
	int sz = ftell(stdin);
	if (!(_buf.rb = calloc(sz, sizeof(char)))) exit(1);
	fseek(stdin, 0, 0);
	fread(_buf.rb, 1, sz, stdin);
}

*/


void solve15552() {
	int T = read_int();
	int a, b;
	for (int i = 0; i < T; i++) {
		a = read_int();
		b = read_int();
		write_int(a + b);
	}
	write(1, _buf.wb, _buf.wbi);
}
int main() {
	struct stat st;
	fstat(0, &st);
	if ((_buf.rb = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, 0, 0)) == MAP_FAILED)
		return 1;
	solve15552();
}


/*
* 2024.1.20 Sat
* 
* Improve readability and convenience of use
*/
