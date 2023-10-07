#include <stdio.h>
long long euler_phi_function(long long N) {
	long long phi = N;
	for (long long i = 2; (i * i) <= N; i++) {
		if (N % i) continue;
		while (!((N /= i) % i));
		phi = phi / i * (i - 1);
	}
	if (N > 1) {
		phi = phi / N * (N - 1);
	}
	return phi;
}
int main() {
	long long N;
	scanf("%lld", &N);
	printf("%lld\n", euler_phi_function(N));
}