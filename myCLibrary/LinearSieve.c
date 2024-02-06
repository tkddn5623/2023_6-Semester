int linear_sieve(int Dest_factors[], int Dest_primes[], const int max) {
	int plen = 0;
	Dest_factors[0] = 0;
	Dest_factors[1] = 0;
	for (int i = 2; i <= max; i++) {
		if (!Dest_factors[i]) Dest_primes[plen++] = i;
		for (int j = 0; j < plen; j++) {
			if (i * Dest_primes[j] > max) break;
			Dest_factors[i * Dest_primes[j]] = Dest_primes[j];
			if (i % Dest_primes[j] == 0) break;
		}
	}
	return plen;
}

/*
* 2024.2.6
* Linear sieve renewal
* (Reference: codeforces.com/blog/entry/54090)
*
/