#define MAXTREE (1 << 21)

typedef struct {
    long long item;
    long long lazy;
} SegmentTree;

void _SG_propagate(SegmentTree segtree[], const int NI, const int NL, const int NR) {
    if (segtree[NI].lazy == 0) return;
    if (NL < NR) {
        segtree[NI * 2].lazy += segtree[NI].lazy;
        segtree[NI * 2 + 1].lazy += segtree[NI].lazy;
    }
    segtree[NI].item += segtree[NI].lazy * (NR - NL + 1);
    segtree[NI].lazy = 0;
}
void _SG_update_impl(SegmentTree segtree[], const int from, const int to, const long long value, const int NI, const int NL, const int NR) {
    _SG_propagate(segtree, NI, NL, NR);
    if (from > NR || to < NL) return;
    if (from <= NL && to >= NR) {
        segtree[NI].lazy += value;
        _SG_propagate(segtree, NI, NL, NR);
        return;
    }
    const int mid = NL + (NR - NL) / 2;
    _SG_update_impl(segtree, from, to, value, NI * 2, NL, mid);
    _SG_update_impl(segtree, from, to, value, NI * 2 + 1, mid + 1, NR);
    segtree[NI].item = segtree[NI * 2].item + segtree[NI * 2 + 1].item;
}
long long _SG_query_impl(SegmentTree segtree[], const int from, const int to, const int NI, const int NL, const int NR) {
    _SG_propagate(segtree, NI, NL, NR);
    if (from > NR || to < NL) return 0LL;
    if (from <= NL && to >= NR) return segtree[NI].item;
    const int mid = NL + (NR - NL) / 2;
    return _SG_query_impl(segtree, from, to, NI * 2, NL, mid) + _SG_query_impl(segtree, from, to, NI * 2 + 1, mid + 1, NR);
}
void SG_construct(SegmentTree _Dest[], const long long items[], const int item_len) {
    int leafs = 1;
    while (leafs < item_len) { leafs <<= 1; }
    for (int i = 0; i < item_len; i++) {
        _Dest[i + leafs].item = items[i];
        _Dest[i + leafs].lazy = 0LL;
    }
    for (int i = leafs - 1; i >= 1; i--) {
        _Dest[i].item = _Dest[i * 2].item + _Dest[i * 2 + 1].item;
        _Dest[i].lazy = 0LL;
    }
    _Dest[0].item = leafs;
}
void SG_update(SegmentTree segtree[], const int from, const int to, const long long value) {
    _SG_update_impl(segtree, from, to, value, 1, 0, segtree[0].item - 1);
}
long long SG_query(SegmentTree segtree[], const int from, const int to) {
    return _SG_query_impl(segtree, from, to, 1, 0, segtree[0].item - 1);
}

/*
* 2024.2.4 Sun
* Lazy propagation first build
*/