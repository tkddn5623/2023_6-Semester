#include<bits/stdc++.h>
#define fastio ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
using namespace std;

int main() {
	fastio;
	int n; cin >> n;
	vector<string> v(n);
	for (int i = 0; i < n; i++) cin >> v[i];
	unordered_map<string, set<string>> M;
	for (auto s : v) {
		for (int i = 0; i <= s.size(); i++) {
			string prefix = s.substr(0, i);
			string suffix = s.substr(i);
			M[prefix].insert(suffix);
		}
	}
	set<set<string>> w;
	for (auto [key, val] : M) w.insert(val);
	cout << w.size() << '\n';
}