#include <stdio.h>
#define EUCLIDFAIL (-1)
#define INVERSEMAX (1000000000)
long long solve3955_extendedEuclidean(long long C, long long K) {
    long long A = C, B = K, S0 = 1, S1 = 0, T0 = 0, T1 = 1;
    while (B) {
        long long Q = A / B;
        long long temp = A % B;
        A = B;
        B = temp;
        temp = S0;
        S0 = S1;
        S1 = temp - S1 * Q;
        temp = T0;
        T0 = T1;
        T1 = temp - T1 * Q;
    }
    if (A != 1) return EUCLIDFAIL;
    while (T0 >= 0) {
        T0 -= C;
        S0 += K;
    }
    return S0;
}
int main() {
    int T;
    long long K, C;
    long long inverse;
    scanf("%d", &T);
    while (T--) {
        scanf("%lld%lld", &K, &C);
        if ((inverse = solve3955_extendedEuclidean(C, K)) == EUCLIDFAIL || inverse > INVERSEMAX) printf("IMPOSSIBLE\n");
        else printf("%lld\n", inverse);
    }
}