#include <bits/stdc++.h>
#define endl "\n"

#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

using namespace std;
using ll = long long;
using ld = long double;

ll inf = 1e9;

ll mod = 1e9 + 7;
ll base = 31;

vector<ll> bases;

void precompute_bases(ll n) {
  bases.push_back(1LL);
  for (int i = 0; i < n; i++) {
    bases.push_back((bases.back() * base) % mod);
  }
}

struct HashCell {
  ll hash;
  ll len;
};

vector<HashCell> st;
string s;

HashCell merge(HashCell a, HashCell b) {
  return HashCell{(((bases[b.len] * a.hash) % mod) + b.hash) % mod, a.len + b.len};
}

void build(ll id, ll l, ll r) {
  if (l + 1 == r) {
    st[id] = HashCell{s[l] - 'a' + 1, 1};
    return;
  }

  ll mid = (l + r) / 2;
  build(id * 2 + 1, l, mid);
  build(id * 2 + 2, mid, r);

  st[id] = merge(st[id * 2 + 1], st[id * 2 + 2]);
}

void update(ll id, ll l, ll r, ll pos, char x) {
  if (l + 1 == r) {
    st[id] = HashCell{x - 'a' + 1, 1};
    return;
  }

  ll mid = (l + r) / 2;
  if (pos < mid) {
    update(id * 2 + 1, l, mid, pos, x);
  } else {
    update(id * 2 + 2, mid, r, pos, x);
  }

  st[id] = merge(st[id * 2 + 1], st[id * 2 + 2]);
}

HashCell query(ll id, ll l, ll r, ll ql, ll qr) {
  if (ql <= l && r <= qr) return st[id];
  if (ql >= r || qr <= l) return HashCell{0, 0};

  ll mid = (l + r) / 2;
  return merge(query(id * 2 + 1, l, mid, ql, qr), query(id * 2 + 2, mid, r, ql, qr));
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  ll n;
  cin >> n;

  cin >> s;

  st.resize(n * 4);

  precompute_bases(n);
  build(0, 0, n);

  ll m;
  cin >> m;

  for (int num_test = 0; num_test < m; num_test++) {
    ll qtype;
    cin >> qtype;

    if (qtype == 1) {
      ll a, b;
      cin >> a >> b;

      cout << query(0, 0, n, a, b).hash << endl;
    } else {
      ll x;
      char c;

      cin >> x >> c;

      update(0, 0, n, x, c);
    }
  }

  return 0;
}
