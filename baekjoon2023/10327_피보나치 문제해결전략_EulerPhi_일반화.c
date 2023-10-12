#include <stdio.h>
#define EUCLIDFAIL (-1)
#define INVERSEMAX (1000000000)
#define NUM_OF_FIB (46)

void solve10327_extendedEuclidean(long long dest[], long long A, long long N) {
    long long S0 = 1, S1 = 0, T0 = 0, T1 = 1;
    while (N) {
        long long Q = A / N;
        long long temp = A % N;
        A = N;
        N = temp;
        temp = S0;
        S0 = S1;
        S1 = temp - S1 * Q;
        temp = T0;
        T0 = T1;
        T1 = temp - T1 * Q;
    }
    //fibonacci: Always A = 1. 
    dest[0] = S0, dest[1] = T0;
}
void solve10327(int fib[], int n) {
    long long euclidResult[2]; //S, T
    int fibsum, min_a, min_b;
    min_b = n / 2;
    min_a = n - min_b;
    for (int i = 2; i < NUM_OF_FIB; i++) {
        if ((fibsum = fib[i] + fib[i - 1]) > n) break;
        int K, temp;
        solve10327_extendedEuclidean(euclidResult, fib[i], fib[i - 1]);
        if (euclidResult[1] <= 0) {
            euclidResult[0] -= fib[i - 1];
            euclidResult[1] += fib[i];
        }
        euclidResult[0] *= n;
        euclidResult[1] *= n;
        // Solve Three Inequation about K
        K = (-euclidResult[0] / fib[i - 1]) + 1;
        if (K < (temp = (euclidResult[1] - euclidResult[0] + fibsum - 1) / fibsum)) 
            K = temp;
        temp = ((euclidResult[1] + fib[i] - 1) / fib[i]) - 1;
        if (K <= temp) {
            min_a = (long long)fib[i] * (-K) + euclidResult[1];
            min_b = (long long)fib[i - 1] * K + euclidResult[0];
        }
    }
    printf("%d %d\n", min_a, min_b);
}
int main() {
    static int fib[NUM_OF_FIB];
    int T;
    fib[0] = 0, fib[1] = 1;
    for (int i = 2; i < NUM_OF_FIB; i++) { fib[i] = fib[i - 1] + fib[i - 2]; }
    scanf("%d", &T);
    while (T--) {
        int n;
        scanf("%d", &n);
        solve10327(fib, n);
    }
}