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
ll recip_el;

vector<ll> bases;

void precompute_bases(ll n) {
  bases.push_back(1LL);
  for (int i = 0; i < n; i++) {
    bases.push_back((bases.back() * base) % mod);
  }
}

ll binpow(ll a, ll n) {
  if (n == 0) return 1;
  if (n & 1) {
    return (a * binpow(a, n - 1)) % mod;
  } else {
    ll q = binpow(a, n / 2);
    return (q * q) % mod;
  }
}

ll compute_hash(ll length, char x) {
  ll division_result = (recip_el * (bases[length] - 1 + mod)) % mod;
  return ((x - 'a' + 1) * division_result) % mod;
}

struct HashCell {
  ll hash;
  ll len;
  char assign = '-';
};

vector<HashCell> st;
string s;

HashCell merge(HashCell a, HashCell b) {
  return HashCell{((bases[b.len] * a.hash) % mod + b.hash) % mod, a.len + b.len, '-'};
}

void push(ll id, ll l, ll r) {
  if (st[id].assign != '-') {
    st[id].hash = compute_hash(st[id].len, st[id].assign);
    if (l + 1 != r) {
      st[id * 2 + 1].assign = st[id].assign;
      st[id * 2 + 2].assign = st[id].assign;
    }
    st[id].assign = '-';
  }
}

void build(ll id, ll l, ll r) {
  if (l + 1 == r) {
    st[id] = HashCell{s[l] - 'a' + 1, 1, '-'};
    return;
  }

  ll mid = (l + r) / 2;
  build(id * 2 + 1, l, mid);
  build(id * 2 + 2, mid, r);

  st[id] = merge(st[id * 2 + 1], st[id * 2 + 2]);
}


HashCell query(ll id, ll l, ll r, ll ql, ll qr) {
  push(id, l, r);
  if (ql >= r || qr <= l) return HashCell{0, 0, '-'};
  if (ql <= l && r <= qr) return st[id];

  ll mid = (l + r) / 2;
  return merge(query(id * 2 + 1, l, mid, ql, qr),
               query(id * 2 + 2, mid, r, ql, qr));
}

void range_update(ll id, ll l, ll r, ll ql, ll qr, ll x) {
  push(id, l, r);

  if (ql >= r || qr <= l) return;
  if (ql <= l && r <= qr) {
    st[id].assign = x;
    st[id].hash = compute_hash(st[id].len, x);

    return;
  }


  ll mid = (r + l) / 2;

  range_update(id * 2 + 1, l, mid, ql, qr, x);
  range_update(id * 2 + 2, mid, r, ql, qr, x);

  st[id] = merge(st[id * 2 + 1], st[id * 2 + 2]);
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

  recip_el = binpow(base - 1, mod - 2);

  ll k;
  cin >> k;

  for (int num_test = 0; num_test < k; num_test++) {
    ll qtype;
    cin >> qtype;

    if (qtype == 1) {
      ll a, b;
      cin >> a >> b;

      cout << query(0, 0, n, a, b).hash << endl;
    } else {
      ll l, r;
      char c;

      cin >> l >> r >> c;

      range_update(0, 0, n, l, r, c);
    }
  }

  return 0;
}
