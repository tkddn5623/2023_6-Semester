#include <stdio.h>
/*long long gcd(long long a, long long b)
{
    int c;
    while (b) { c = a % b; a = b; b = c; }
    return a;
}*/
long long extendedEuclidean(long long A, long long N) {
    long long temp, Q, S0 = 1, S1 = 0/*, T0 = 0, T1 = 1*/;
    while (N) {
        Q = A / N;
        temp = A % N;
        A = N;
        N = temp;

        /*temp = A;
        A = N;
        N = temp - N * Q;*/

        temp = S0;
        S0 = S1;
        S1 = temp - S1 * Q;

        /*temp = T0;
        T0 = T1;
        T1 = temp - T1 * Q;*/
    }
    if (A != 1) return -1;
    return S0;
}
int main() {
    long long A, N;
    long long inverse;
    scanf("%lld%lld", &N, &A);
    printf("%lld ", N - A);
    if ((inverse = extendedEuclidean(A, N)) >= -1) printf("%lld\n", inverse);
    else printf("%lld\n", N + inverse);
}