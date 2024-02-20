#include <cstdio>
#include <map>

void solve7662(int Q) {
	using namespace std;
	map<int, int> tree;

	for (int i = 0; i < Q; i++) {
		char op;
		int num;

		scanf(" %c%d", &op, &num);

		if (op == 'I') {
			auto search = tree.find(num);
			if (search == tree.end()) {
				tree.insert({ num, 1 });
			}
			else {
				search->second++;
			}
		}

		if (op == 'D' && !tree.empty()) {
			if (num == -1) {
				auto search = tree.begin();
				if (--search->second == 0) {
					tree.erase(search);
				}
			}
			else {
				auto search = prev(tree.end());
				if (--search->second == 0) {
					tree.erase(search);
				}
			}
		}
	}

	if (tree.empty()) printf("EMPTY\n");
	else printf("%d %d\n", prev(tree.end())->first, tree.begin()->first);
	
}
int main() {
#ifndef ONLINE_JUDGE
	freopen("i.txt", "r", stdin);
#endif
	int T;
	scanf("%d", &T);
	do {
		int Q;
		scanf("%d", &Q);
		solve7662(Q);
	} while (--T > 0);
}