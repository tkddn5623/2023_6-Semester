#define MAXTREE (1 << 21)
void SG_construct(long long _Dest[], const long long items[], const int item_len) {
	int leafs = 1;
	while (leafs < item_len) { leafs <<= 1; }
	for (int i = 0; i < item_len; i++) {
		_Dest[i + leafs] = items[i];
	}
	for (int i = leafs - 1; i >= 1; i--) {
		_Dest[i] = _Dest[i * 2] + _Dest[i * 2 + 1];
	}
	_Dest[0] = leafs;
}
long long SG_get(const long long segtree[], int from, int to) {
	long long ret = 0;
	from += segtree[0]; to += segtree[0];
	while (from <= to) {
		if (from % 2 == 1) ret += segtree[from++];
		if (to % 2 == 0) ret += segtree[to--];
		from /= 2; to /= 2;
	}
	return ret;
}
void SG_update(long long segtree[], int index, const long long value) {
	index += segtree[0];
	segtree[index] = value;
	while ((index /= 2) >= 1) {
		segtree[index] = segtree[index * 2] + segtree[index * 2 + 1];
	}
}

long long _SG_get_topdown_impl(const long long segtree[], const int from, const int to, const int NI, const int NL, const int NR) {
	if (from > NR || to < NL) return 0;
	if (from <= NL && to >= NR) return segtree[NI];
	const int mid = NL + (NR - NL) / 2;
	return _SG_get_topdown_impl(segtree, from, to, NI * 2, NL, mid) + _SG_get_topdown_impl(segtree, from, to, NI * 2 + 1, mid + 1, NR);
}
long long SG_get_topdown(const long long segtree[], const int from, const int to) {
	return _SG_get_topdown_impl(segtree, from, to, 1, 0, segtree[0] - 1);
}


/*
* 2023.2.21 Tue
* items and _Dest are assumed to be allocated 'ENOUGHLY'.
* 
* e.g. 
* #define MAXSIZE (1000000)
* #define MAXTREE (1 << 21)
* Because 2^20 < 1m < 2^21. 
* 
* Reference: jeonggyun.tistory.com/245
*
*
* 2024.2.3 Sat
* Top-down approach added
*/
